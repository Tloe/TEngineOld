#ifndef TECLIENT_H
#define TECLIENT_H

#include "TEConnection.h"

namespace TE {
    namespace Net {
        class Packet;
    }

    namespace Net {
        class Client {
          public:
            Client();
            ~Client();

            void SendPacket(Packet &packet);

          private:
            // Connection m_connection;
        };
    }
}

#endif