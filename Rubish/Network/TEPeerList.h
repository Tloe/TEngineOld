/**
 *	\file		TEPeerList.h
 *  \author		Terje Loe
 *  \brief		Defenitions for PeerList class
 *				holds a map of peers
 */

#ifndef TEPEERLIST_H
#define TEPEERLIST_H

#include <TEPeer.h>
#include <unordered_map>

namespace TE
{
	namespace Network
	{
		class PeerList
		{
		public:
			PeerList();

			void Add(const Peer &peer);
			bool Empty();
			Peer& GetPeer(unsigned id)
			{
				return m_peers[id];
			}

			Peer* SearchEnetPeer(const ENetPeer *enetPeer)
			{
				std::unordered_map<unsigned,Peer>::iterator itr = m_peers.begin();
				while(itr->second.GetEnetPeer() != enetPeer && itr != m_peers.end())
					itr++;

				if(itr == m_peers.end())
					return NULL;
				else
					return &itr->second;
			}

			unsigned Size()
			{
				return m_peers.size();
			}
		private:
			std::unordered_map<unsigned,Peer> m_peers;
			unsigned m_peerIDs;
		};
	}
}

#endif