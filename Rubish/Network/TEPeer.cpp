#include <TEPeer.h>

TE::Network::Peer::Peer( ENetPeer *enetPeer, ENetHost *enetHost )
{
	m_enetPeer = enetPeer;
	m_enetHost = enetHost;
}

TE::Network::Peer::Peer( const Peer& src )
{
	m_enetPeer = src.m_enetPeer;
	m_enetHost = src.m_enetHost;
	m_id = src.m_id;
}

TE::Network::Peer::~Peer()
{

}

TE::Network::Peer& TE::Network::Peer::operator=(const Peer& rhs)
{
	if(&rhs == this) return *this;

	m_enetPeer = rhs.m_enetPeer;
	m_enetHost = rhs.m_enetHost;
	m_id = rhs.m_id;

	return *this;
}


void TE::Network::Peer::Disconnect()
{
	ENetEvent event;
	enet_peer_disconnect (m_enetPeer, 0);

	while (enet_host_service (m_enetHost, & event, 1000) > 0)
	{
		switch (event.type)
		{
		case ENET_EVENT_TYPE_RECEIVE:
			{
				enet_packet_destroy (event.packet);
				break;
			}
		case ENET_EVENT_TYPE_DISCONNECT:
			{
				std::cout << "Disconnection succeeded." << std::endl;
				return;
			}
		}
	}

	enet_peer_reset (m_enetPeer);
}

void TE::Network::Peer::SetId( unsigned id )
{
	m_id = id;
}

unsigned TE::Network::Peer::GetId()
{
	return m_id;
}

ENetPeer * TE::Network::Peer::GetEnetPeer() const
{
	return m_enetPeer;
}
