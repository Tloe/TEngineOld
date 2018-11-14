/**
 *	\file		TEHost.h
 *  \author		Terje Loe
 *  \brief		Defenitions for Host class
 *				Manages a host
 */

#ifndef TEHOST_H
#define TEHOST_H

#include <enet/enet.h>
#include <iomanip>
#include <ios>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <TEPacking.h>
#include <TEPeerList.h>

namespace TE
{
	namespace Network
	{
		class Host
		{
		public:
			Host();

			~Host();

			void Update();
			bool Start(bool isServer, unsigned peerCount = 1, const std::string &addrStr = "", unsigned port = 1234);
			bool Connect(const std::string &addrStr, unsigned port);
			void SendPacket(const Packet &packet, unsigned peerId = 0);
		private:
			static I32									m_hostCount;
			ENetHost									*m_host;
			PeerList									m_peers;
			std::unordered_map<unsigned, PacketQue>		m_packetQuesOut;
			PacketQue									m_packetQueInn;

			void SendPacketQues();
		};
	}
}

#endif

