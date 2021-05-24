#ifndef TECLIENT_H
#define TECLIENT_H

#include "TEConnection.h"

namespace TE::Net {
  class Packet;

  class Client {
  public:
    Client();
    ~Client();

    void SendPacket(Packet &packet);

  private:
    // Connection m_connection;
  };
}

#endif
