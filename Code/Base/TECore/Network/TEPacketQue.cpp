#include "TEPacketQue.h"
#include "TEPacket.h"

void TE::Net::PacketQue::Add( const Packet& packet )
{
	m_packets.push_back(packet);
}

void TE::Net::PacketQue::Pack( Packet &packet )
{
    packet.BeginPacket(PacketType::Packet);

	unsigned numPackets = m_packets.size();
	packet.WriteDynamicU32(numPackets);
	for (unsigned i = 0; i < numPackets; ++i)
	{
		packet.WriteBinaryPacket(m_packets[i]);
	}

	packet.EndPacket();
}

void TE::Net::PacketQue::Unpack( Packet &packet )
{
	unsigned numPackets;
	packet.ReadDynamicU32(numPackets);
    Packet tmpPacket;
	for (unsigned i = 0; i < numPackets; ++i)
	{
		packet.ReadBinaryPacket(tmpPacket);
		m_packets.push_back(tmpPacket);
	}
}

void TE::Net::PacketQue::Clear()
{
	m_packets.clear();
}

std::vector<TE::Net::Packet>& TE::Net::PacketQue::GetPackets()
{
	return m_packets;
}

