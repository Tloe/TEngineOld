#ifndef TERELIABLECONNECTION_H
#define TERELIABLECONNECTION_H

#include "TEConnection.h"
#include "TEReliabilityControl.h"

namespace TE {
namespace Net {
    class ReliableConnection : public Connection {
      public:
        ReliableConnection(Socket &socket, const Address &address, U32 timeout, Connection::Mode connectionMode, U32 maxSequence = 0xffffff);
        ~ReliableConnection();

        virtual bool SendPacket(Net::Packet &packet);
        virtual bool ReceivePacket(Net::Packet &packet);
        void Update(U64 deltaTime);
        ReliabilityControl &GetReliabilityControl();

      private:
        virtual void OnStop();
        virtual void OnDisconnect();
        void ClearData();

        ReliabilityControl m_reliabilityControl;
        U32 m_previousReceivedSeqNo;
    };
}
}

#endif
