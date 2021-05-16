#ifndef TENETWORKPLATFORM_H
#define TENETWORKPLATFORM_H

#include "TEAddress.h"
#include "TEDataTypes.h"
#include "TESocketIncludes.h"

#include <list>
#include <map>
#include <vector>

namespace TE {
    namespace Net {
        class Packet;
    }
    namespace Net {
        class Address;
    }

    namespace Net {
        class Socket {
          public:
            Socket(U16 protocolId);
            ~Socket();

            bool Open(const std::string &port, IPFamily ipFamily);
            void Close();
            bool IsOpen() const;
            bool SendTo(const Address &address, Packet &packet);
            bool GetReceivedPacketFrom(const Address &address, Packet &packet);
            void NewConnection(const Address &address);
            bool HasIncomingConnection(Address &address);
            void ConnectionTimeout(const Address &address);
            void Update();

          private:
            typedef std::list<Address> AddressList;
            typedef std::list<Packet> PacketList;
            typedef std::map<Address, PacketList> ReceivedPacketMap;

            std::string debugPort;
            AddressList m_newIncomming;
            ReceivedPacketMap m_receivedPackets;
            U16 m_protocolId;
            I32 m_socket;
            std::vector<U8> m_receiveBuffer;
        };

        bool InitializeSockets();
        bool CleanupSockets();
    }
}

#endif
