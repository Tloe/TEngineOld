#include <TEPeerList.h>

TE::Network::PeerList::PeerList() : m_peerIDs(1)
{

}

void TE::Network::PeerList::Add( const Peer &peer )
{
	m_peers[m_peerIDs] = peer;
	m_peerIDs++;
}

bool TE::Network::PeerList::Empty()
{
	return m_peers.empty();
}

