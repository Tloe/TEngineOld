#include "NetworkTest.h"
#include "TEAddress.h"
#include "TEDataTypes.h"
#include "TEFlowControl.h"
#include "TEPacket.h"
#include "TERandomNumberGenerators.h"
#include "TEReliableConnection.h"
#include "TESocket.h"
#include "TETimer.h"
#include <iostream>
#include <string>

int NetworkTestMain() {
    const std::string serverPort  = "4444";
    const std::string clientPort1 = "4445";
    const std::string clientPort2 = "4446";

    const U64 deltaTime           = 33333ULL;

    const bool printAcks          = false;

    enum Mode {
        Client,
        Server
    };

    Mode mode = Server;
    TE::Net::Address address;

    std::cout << "Server or client? (s/c)" << std::endl;
    char c = ' ';
    while (c != 's' && c != 'c') {
        std::cin >> c;
    }
    char cn = ' ';
    if (c == 'c') {
        mode = Client;
        std::cout << "Client 1 or 2? (1/2)" << std::endl;
        while (cn != '1' && cn != '2') {
            std::cin >> cn;
        }
    }

    if (!TE::Net::InitializeSockets()) {
        std::cout << "failed to initialize sockets" << std::endl;
        return 1;
    }
    TE::Net::Socket socket(4032);
    const std::string port = (mode == Server) ? serverPort : (cn == '1') ? clientPort1
                                                                         : clientPort2;
    std::cout << port << std::endl;
    assert(socket.Open(port, TE::Net::IPFamily::IPv4));

    if (c == 'c') {
        mode = Client;
        TE::Net::Address address;
        address.SetAddress("127.0.0.1", serverPort, TE::Net::IPFamily::IPv4);

        TE::Net::ReliableConnection connection(socket,
                                               address,
                                               TE::Time::Microseconds::Second * 10,
                                               TE::Net::Connection::Mode::Client);

        while (true) {
            socket.Update();
            connection.Update(deltaTime);

            TE::Net::Packet clientPacket;
            clientPacket.BeginPacket(TE::Net::PacketType::Packet);
            if (cn == '1')
                clientPacket.WriteString("client1 -> Server packet");
            else
                clientPacket.WriteString("client2 -> Server packet");
            clientPacket.EndPacket();

            connection.SendPacket(clientPacket);

            TE::Net::Packet incomingPacket;
            while (connection.ReceivePacket(incomingPacket)) {
                incomingPacket.StartReading();
                std::string str;
                incomingPacket.ReadString(str);

                TE::Net::Packet message;
                incomingPacket.ReadBinaryPacket(message);
                message.StartReading();

                U32 count;
                message.ReadU32(count);
                F32 f;
                message.ReadF32(f);
                std::cout << str << " count: " << count << " float: " << f;
                // std::cout << str << " rtt: " << connection.GetReliabilityControl().GetRoundTripTime() << std::endl;
            }

            std::cout << std::endl;
            TE::Time::Wait(deltaTime, TE::Time::Units::Microseconds);
        }
    } else {
        std::vector<TE::Net::ReliableConnection> connections;
        while (true) {
            socket.Update();
            for (auto &connection : connections)
                connection.Update(deltaTime);

            TE::Net::Address newAddress;
            while (socket.HasIncomingConnection(newAddress)) {
                connections.push_back(TE::Net::ReliableConnection(socket, newAddress, TE::Time::Microseconds::Second * 10, TE::Net::Connection::Mode::Server));
            }

            if (!connections.empty()) {

                TE::Net::Packet broadcastPacket;
                broadcastPacket.BeginPacket(TE::Net::PacketType::Packet);
                broadcastPacket.WriteString("Broadcast packet");

                TE::Net::Packet message;
                message.BeginPacket();
                static U32 countn = 0;
                message.WriteU32(countn);
                F32 f = TE::Utils::RandomF32Generator(0.0f, 0.1f)();
                std::cout << "count: " << countn++ << " float " << f;
                message.WriteF32(f);
                message.EndPacket();
                broadcastPacket.WriteBinaryPacket(message);
                broadcastPacket.EndPacket();

                I32 count = 0;
                for (auto &connection : connections) {
                    if (count++ == 0)
                        std::cout << " - 1 - ";
                    else
                        std::cout << " - 2 -";
                    connection.SendPacket(broadcastPacket);
                }
            }

            I32 count = 0;
            for (auto &connection : connections) {
                if (count++ == 0)
                    std::cout << " - 1 - ";
                else
                    std::cout << " - 2 - ";
                TE::Net::Packet incomingPacket;
                while (connection.ReceivePacket(incomingPacket)) {

                    incomingPacket.StartReading();
                    std::string str;
                    incomingPacket.ReadString(str);
                    // std::cout << str << " rtt: " << connection.GetReliabilityControl().GetRoundTripTime() << std::endl;
                }
            }

            std::cout << std::endl;
            TE::Time::Wait(deltaTime, TE::Time::Units::Microseconds);
        }
    }

    /*TE::Net::ReliableConnection connection(socket, TE::Time::Microseconds::Second * 10);

    if (!connection.Initialize(port, TE::Net::IPFamily::IPv4))
        {
                std::cout << "could not start connection on port " << port << std::endl;
                return 1;
        }

        if (mode == Client)
                connection.Connect(address);
        else
                connection.Listen();

        bool connected = false;
        U64 sendAccumulator = 0;
        U64 statsAccumulator = 0;

    TE::Net::FlowControl flowControl;

        while (true)
        {
                // update flow control

                if (connection.IsConnected())
                {
                        flowControl.Update(deltaTime, connection.GetReliabilityControll().GetRoundTripTime());
                }

                const U32 sendRate = flowControl.GetSendRate();

                // detect changes in connection state

        if ( mode == Server && connected && !connection.IsConnected() )
                {
                        flowControl.Reset();
                        std::cout << "reset flow control" << std::endl;
                        connected = false;
                }

                if ( !connected && connection.IsConnected() )
                {
                        std::cout << "client connected to server" << std::endl;
                        connected = true;
                }

                if ( !connected && connection.ConnectFailed() )
                {
                        std::cout << "connection failed" << std::endl;
                        break;
                }

                // send and receive packets

                sendAccumulator += deltaTime;

                while ( sendAccumulator > TE::Time::Microseconds::Second / sendRate )
                {
            std::string messageData0("Hello,");
            std::string messageData1(" world!");

            TE::Net::Packet message0;
            message0.BeginPacket();
            message0.WriteString(messageData0);
            message0.EndPacket();

            TE::Net::Packet message1;
            message1.BeginPacket();
            message1.WriteString(messageData1);
            message1.EndPacket();

            TE::Net::Packet packet;
            packet.BeginPacket(TE::Net::PacketType::Packet);
            U32 messageNum = 2;
            packet.WriteU32(messageNum);
            packet.WriteBinaryPacket(message0);
            packet.WriteBinaryPacket(message1);
                        packet.EndPacket();
                        connection.SendPacket(packet);
                        sendAccumulator -= TE::Time::Microseconds::Second / sendRate;
                }

                while ( true )
                {
            TE::Net::Packet packet;
                        if(!connection.ReceivePacket(packet))
                                break;

            packet.StartReading();
            U32 numMessages;
            packet.ReadU32(numMessages);
            std::cout << "Received: " << numMessages;
            for(U32 i = 0; i < numMessages; ++i)
            {
                TE::Net::Packet message;
                packet.ReadBinaryPacket(message);
                message.StartReading();
                std::string str;
                message.ReadString(str);
                std::cout << str;
            }
            std::cout << std::endl;
                }

                // show packets that were acked this frame

                if(printAcks)
                {
                        std::vector<U32> acks = connection.GetReliabilityControll().GetAcks();
                        if ( acks.size() > 0 )
                        {
                                std::cout << "acks: ";
                                for (auto itr : acks)
                                {
                                        std::cout << itr << " ";
                                }
                                std::cout << std::endl;
                        }
                }
                // update connection

                connection.Update(33333ULL);

                // show connection stats

                statsAccumulator += deltaTime;

                while ( statsAccumulator >= 250000ULL && connection.IsConnected() )
                {
                        U64 rtt = connection.GetReliabilityControll().GetRoundTripTime();

                        U32 sent_packets = connection.GetReliabilityControll().GetSentPackets();
                        U32 acked_packets = connection.GetReliabilityControll().GetAckedPackets();
                        U32 lost_packets = connection.GetReliabilityControll().GetLostPackets();

                        F32 sent_bandwidth = connection.GetReliabilityControll().GetSentBandwidth_kbit();
                        F32 acked_bandwidth = connection.GetReliabilityControll().GetAckedBandwidth_kbit();

            //std::cout << "rtt " << rtt << std::endl;
                        //std::cout << "sent " << sent_packets << std::endl;
                        //std::cout << "acked " << acked_packets << ", lost "
                        //	<< lost_packets << "("
                        //	<<  ((sent_packets > 0) ? (float) lost_packets / (float) sent_packets * 100.0f : 0)
                        //	<< ")" << std::endl;
            //std::cout << "sent bandwidth = " << sent_bandwidth << "kbps" << std::endl;
            //std::cout << "acked bandwith = " << acked_bandwidth << "kbps" << std::endl << std::endl;

                        statsAccumulator -= 250000ULL;
                }

                TE::Time::Wait(deltaTime, TE::Time::Units::Microseconds);
        }
*/
    socket.Close();
    TE::Net::CleanupSockets();

    return 0;
}
