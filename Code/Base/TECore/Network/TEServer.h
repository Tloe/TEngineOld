#ifndef TESERVER_H
#define TESERVER_H

#include "TEDataTypes.h"

#include "TEConnection.h"
#include <unordered_map>

namespace TE::Net {
  class Packet;

  class Server {
  public:
    Server();
    ~Server();

    void SendPacket(I32 clientId, Packet &packet);
    void BroadcastPacket(Packet &packet);

  private:
    typedef std::unordered_map<I32, Connection> ConnectionMap;

    ConnectionMap m_connectionMap;
  };
}

#endif
