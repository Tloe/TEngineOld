#ifndef TENETWORKMANAGER_H
#define TENETWORKMANAGER_H

#include "TEMessageHandler.h"
#include "TEReliableConnection.h"
#include "TEFlowControl.h"
#include "TESocket.h"
#include "TEPacket.h"
#include "TEEventHandler.h"

#include <map>
#include <list>

namespace TE
{
    namespace Event { class EnvironmentUpdateEvent; }


    namespace Network
    {
        class NetworkManager : public Event::EventHandler
        {
        public:
            typedef void (*MessageCallback)(Net::Packet&);

            NetworkManager();
            ~NetworkManager();

            virtual void HandleEvent(Event::EnvironmentUpdateEvent &environmentUpdateEvent);

            void SetServerMode(bool value);
            void SetPort(const std::string & port);
            void SetIpFamily(Net::IPFamily ipFamily);

            void Initialize();
            void Cleanup();

            bool IsServer();

            ConnectionId Connect(Net::Address &address);
            void Update(U64 deltaTime, U64 time);

            void AddNetworkObject(I32 objectId, TE::Network::NetworkObjectSPtr &networkObject);
            void AddMessageCallback(I32 packetId, MessageCallback messageCallback);
            void MapConnectionToObjectId(I32 connectionId, I32 objectId);

            MessageHandler& GetMessagehandler();
        private:
            struct ConnectionData
            {
                U64 timeSinceLastPacket;
                I32 framesUntilNextPacket;
                Net::ReliableConnection connection;
                Net::FlowControl flowControl;
            };
            typedef std::map<U32, ConnectionData> ConnectionMap;

            void ReceiveQue(U32 connectionId, Net::Connection & connection, U64 time);
            void CheckAcks(U32 connectionId, Net::ReliableConnection &connection);
            void SendQue(U32 connectionId, ConnectionData &connectionData, U64 deltaTime);
            void QueSent(ConnectionData &connectionData);

            bool UpdateConnection(U32 connectionId, ConnectionData &connectionData, U64 deltaTime);
            void CleanupConnection(U32 connectionId);

            bool m_server;
            std::string m_port;
            Net::IPFamily m_ipFamily;
            Net::Socket m_socket;
            U64 m_microsecondsPrFrame;
            ConnectionMap m_connections;
            MessageHandler m_messageHandler;
        };

    }
}

#endif
