/**
 *	\file		TEWPeer.h
 *  \author		Terje Loe
 *  \brief		Defenitions for Peer class
 *				sets up a network peer using enet as a thin client on top of tcp.
 */

#ifndef TEPEER_H
#define TEPEER_H

#include <enet/enet.h>
#include <iostream>

namespace TE
{
	namespace Network
	{
		class Peer
		{
		public:
			Peer(){};

			Peer(ENetPeer *enetPeer, ENetHost *enetHost);

			~Peer();

			Peer(const Peer& src);

			Peer& operator=(const Peer& rhs);

			void Disconnect();

			void SetId(unsigned id);

			unsigned GetId();

			ENetPeer *GetEnetPeer() const;
		private:
			ENetPeer *m_enetPeer;
			ENetHost *m_enetHost;
			unsigned m_id;
		};
	}
}

#endif