#ifndef TEPACKETQUE_H
#define TEPACKETQUE_H

#include "TEPacket.h"
#include <vector>

namespace TE::Net {
  class Packet;

  class PacketQue {
  public:
    void Add(const Packet &packet);
    void Pack(Packet &packet);
    void Unpack(Packet &packet);
    void Clear();
    std::vector<Packet> &GetPackets();

  private:
    std::vector<Packet> m_packets;
  };
}

#endif
