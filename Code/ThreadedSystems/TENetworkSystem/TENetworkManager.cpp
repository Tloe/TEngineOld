#include "TENetworkManager.h"
#include "TEEnvironment.h"
#include "TEEnvironmentUpdateEvent.h"
#include "TETime.h"

namespace {
    const U32 connectionTimeout = TE::Time::Microseconds::Second * 10;
    const U16 protocolId        = 4242;
    const U64 keepAliveInterval = TE::Time::Microseconds::Second / 3;

    U32 GetUniqueConnectionId() {
        static U32 connectionId = 0;

        return connectionId++;
    }

    TE::Net::Packet GenerateKeepAlivePacket() {
        TE::Net::Packet packet;

        packet.BeginPacket(TE::Net::PacketType::Packet);

        packet.WriteU32(0);

        packet.EndPacket();
        return packet;
    }
}

TE::Network::NetworkManager::NetworkManager()
    : m_server(false),
      m_port("4444"),
      m_ipFamily(Net::IPFamily::IPv4),
      m_socket(::protocolId),
      m_microsecondsPrFrame(0) {}

TE::Network::NetworkManager::~NetworkManager() {}

void TE::Network::NetworkManager::HandleEvent(
    Event::EnvironmentUpdateEvent &environmentUpdateEvent) {
    if (environmentUpdateEvent.GetName() == "Framerate") {
        if (environmentUpdateEvent.GetValue().GetString() == "30Hz") {
            m_microsecondsPrFrame = 33333;
        } else if (environmentUpdateEvent.GetValue().GetString() == "60Hz") {
            m_microsecondsPrFrame = 16666;
        }
    }
}

void TE::Network::NetworkManager::SetServerMode(bool value) { m_server = value; }

void TE::Network::NetworkManager::SetPort(const std::string &port) { m_port = port; }

void TE::Network::NetworkManager::SetIpFamily(TE::Net::IPFamily ipFamily) {
    m_ipFamily = ipFamily;
    assert(m_ipFamily == Net::IPFamily::IPv4 && "IPv6 needs some more work");
}

void TE::Network::NetworkManager::Initialize() {
    if (!Net::InitializeSockets()) {
        // TODO - log critical
        exit(-1);
    }
    if (!m_socket.Open(m_port, m_ipFamily)) {
        // TODO - log critical
        exit(-1);
    }
}

void TE::Network::NetworkManager::Cleanup() {
    m_socket.Close();
    Net::CleanupSockets();
}

bool TE::Network::NetworkManager::IsServer() { return m_server; }

TE::Network::ConnectionId TE::Network::NetworkManager::Connect(TE::Net::Address &address) {
    Net::Connection::Mode connectionMode;

    if (m_server)
        connectionMode = Net::Connection::Mode::Server;
    else
        connectionMode = Net::Connection::Mode::Client;

    ConnectionData connectionData{0, 0, {m_socket, address, ::connectionTimeout, connectionMode}};

    ConnectionId connectionId = ::GetUniqueConnectionId();

    m_connections.insert(std::make_pair(connectionId, connectionData));

    m_messageHandler.AddConnection(connectionId);

    std::cout << "Connect!" << std::endl;

    return connectionId;
}

void TE::Network::NetworkManager::Update(U64 deltaTime, U64 time) {
    assert(m_microsecondsPrFrame != 0);

    m_socket.Update();
    Net::Address address;
    while (m_socket.HasIncomingConnection(address)) {
        Connect(address);
    }

    if (m_server)
        m_messageHandler.GenerateObjectUpdateMessages();

    for (auto itr = m_connections.begin(); itr != m_connections.end();) {
        --itr->second.framesUntilNextPacket;

        ConnectionId connectionId = itr->first;
        if (UpdateConnection(connectionId, itr->second, deltaTime)) {
            if (itr->second.framesUntilNextPacket <= 0) {
                SendQue(connectionId, itr->second, deltaTime);
            }
            ReceiveQue(connectionId, itr->second.connection, time);
            CheckAcks(connectionId, itr->second.connection);

            ++itr;
        } else {
            ++itr;
            CleanupConnection(connectionId);
        }
    }
}

void TE::Network::NetworkManager::AddNetworkObject(I32 objectId,
                                                   TE::Network::NetworkObjectSPtr &networkObject) {
    m_messageHandler.AddNetworkObject(objectId, networkObject);
}

void TE::Network::NetworkManager::ReceiveQue(U32 connectionId,
                                             Net::Connection &connection,
                                             U64 time) {
    Net::Packet packet;
    while (connection.ReceivePacket(packet)) {
        m_messageHandler.HandleQuePacket(connectionId, packet, time);
    }
}

void TE::Network::NetworkManager::CheckAcks(U32 connectionId, Net::ReliableConnection &connection) {
    std::vector<U32> &acks = connection.GetReliabilityControl().GetAcks();
    if (!acks.empty()) {
        m_messageHandler.CheckAcks(connectionId, acks);
    }
}

void TE::Network::NetworkManager::SendQue(U32 connectionId,
                                          ConnectionData &connectionData,
                                          U64 deltaTime) {
    if (m_messageHandler.HasQuedMessages(connectionId)) {
        U32 sequenceNo     = connectionData.connection.GetReliabilityControl().GetLocalSequence();
        Net::Packet packet = m_messageHandler.GenerateQuePacket(connectionId, sequenceNo);
        if (connectionData.connection.SendPacket(packet))
            QueSent(connectionData);
        else
            std::cout << "WARNING: SendPacket failed!" << std::endl;
    } else {
        if (connectionData.timeSinceLastPacket > ::keepAliveInterval) {
            static Net::Packet keepAlivePacket = ::GenerateKeepAlivePacket();
            if (connectionData.connection.SendPacket(keepAlivePacket))
                QueSent(connectionData);
            else
                std::cout << "WARNING: SendPacket failed!" << std::endl;
        } else {
            connectionData.timeSinceLastPacket += deltaTime;
        }
    }
}

void TE::Network::NetworkManager::QueSent(ConnectionData &connectionData) {
    connectionData.timeSinceLastPacket = 0;
    if (connectionData.flowControl.GetSendRate() == 30) {
        if (Time::Microseconds::Second / m_microsecondsPrFrame == 30)
            connectionData.framesUntilNextPacket = 1;
        else if (Time::Microseconds::Second / m_microsecondsPrFrame == 60)
            connectionData.framesUntilNextPacket = 2;
    } else if (connectionData.flowControl.GetSendRate() == 10) {
        if (Time::Microseconds::Second / m_microsecondsPrFrame == 30)
            connectionData.framesUntilNextPacket = 3;
        else if (Time::Microseconds::Second / m_microsecondsPrFrame == 60)
            connectionData.framesUntilNextPacket = 6;
    }
}

bool TE::Network::NetworkManager::UpdateConnection(U32 connectionId,
                                                   ConnectionData &connectionData,
                                                   U64 deltaTime) {
    connectionData.connection.Update(deltaTime);
    U64 rtt = connectionData.connection.GetReliabilityControl().GetRoundTripTime();
    connectionData.flowControl.Update(deltaTime, rtt);

    if (!(connectionData.connection.IsConnecting() || connectionData.connection.IsConnected()))
        return false;

    if (m_server && connectionData.framesUntilNextPacket <= 0) {
        m_messageHandler.QueObjectUpdateMessages(connectionId);
    }

    return true;
}

void TE::Network::NetworkManager::CleanupConnection(U32 connectionId) {
    m_messageHandler.RemoveConnection(connectionId);
    m_connections.erase(connectionId);
}

void TE::Network::NetworkManager::AddMessageCallback(
    I32 packetId,
    TE::Network::NetworkManager::MessageCallback messageCallback) {}

void TE::Network::NetworkManager::MapConnectionToObjectId(I32 connectionId, I32 objectId) {
    m_messageHandler.MapConnectionToObjectId(connectionId, objectId);
}

TE::Network::MessageHandler &TE::Network::NetworkManager::GetMessagehandler() {
    return m_messageHandler;
}
