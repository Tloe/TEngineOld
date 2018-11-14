#include <TEHost.h>

I32 TE::Network::Host::m_hostCount = 0;

TE::Network::Host::Host() : m_host(NULL)
{
	if (m_hostCount == 0)
	{
		if(enet_initialize() != 0)
		{
			//Log: Could not initialize enet.
		}
	}
	m_hostCount++;
}

TE::Network::Host::~Host()
{
	if (m_host)
	{
		enet_host_destroy(m_host);
		m_host = NULL;
	}

	m_hostCount--;
	if (m_hostCount <= 0)
	{
		enet_deinitialize();
	}
}

bool TE::Network::Host::Start( bool isServer, unsigned peerCount /*= 1*/, const std::string &addrStr /*= ""*/, unsigned port /*= 1234*/ )
{
	if (isServer)
	{
		ENetAddress address;
		address.port = port;
		if (addrStr.empty())
		{
			address.host = ENET_HOST_ANY;
		}
		else
		{
			enet_address_set_host(&address, addrStr.c_str());
		}

		m_host = enet_host_create(&address, peerCount, 2, 0, 0);
		
		if (!m_host)
		{
			//Log: Could not create server host.
			return false;
		}
	}
	else
	{
		m_host = enet_host_create(NULL, peerCount, 2, 57600, 57600);
		if (!m_host)
		{
			//Log: Could not create client host.
			return false;
		}

		if(!addrStr.empty() && !Connect(addrStr, port))
		{
			//Log: Could not connect to server at address/port
			return false;
		}
	}

	return true;
}

void TE::Network::Host::SendPacket(const Packet &packet, unsigned peerId  /* = 0 */)
{
	if (m_peers.Empty()) return;

	m_packetQuesOut[peerId].Add(packet);
}

void TE::Network::Host::Update()
{
	if (!m_host) return;

	SendPacketQues();

	ENetEvent event;
	while (enet_host_service (m_host, &event, 1) > 0)
	{
		switch (event.type)
		{
			case ENET_EVENT_TYPE_CONNECT:
			{
				std::cout << "A new client connected from "
					<< std::hex << std::uppercase << event.peer->address.host << std::nouppercase
					<< ":" <<
					std::hex << std::uppercase << event.peer->address.port << std::nouppercase
					<< std::endl;

				// Store any relevant client information here.
				//Taken out as data needs to copied in and have to make sure its deleted
				//event.peer->data = "Client information";

				Peer peer(event.peer, m_host);
				m_peers.Add(peer);

				break;
			}
		case ENET_EVENT_TYPE_RECEIVE:
			{
				
				Peer* peer = m_peers.SearchEnetPeer(event.peer);

				if (peer)
				{
					std::cout << "A packet of length " << event.packet->dataLength << " containing "
						<< event.packet->data << " was received from "
						<< std::hex << std::uppercase << peer->GetEnetPeer()->address.host << std::nouppercase
						<< " on channel " << (I32)event.channelID 
						<< std::endl;

					Packet tmpPack(event.packet->data, event.packet->dataLength / 8);
					m_packetQueInn.Clear();
					m_packetQueInn.Unpack(tmpPack);
				}
			
				// Clean up the packet now that we're done using it.
				enet_packet_destroy (event.packet);

				break;
			}
		case ENET_EVENT_TYPE_DISCONNECT:
			{
				std::cout << event.peer->data << "disconnected.";

				/* Reset the peer's client information. */

				event.peer -> data = NULL;
			}
		}
	}
}

bool TE::Network::Host::Connect( const std::string &addrStr, unsigned port )
{
	if (addrStr.empty())
	{
		return false;
	}
	else
	{
		ENetAddress addresse;
		enet_address_set_host(&addresse, addrStr.c_str());
		addresse.port = port;

		//Todo: Add validation key
        ENetPeer *enetPeer = enet_host_connect(m_host, &addresse, 2, 0);

		if (enetPeer == NULL) return false;

		ENetEvent event;
		if (enet_host_service(m_host, &event, 2000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
		{
			Peer peer(enetPeer, m_host);
			m_peers.Add(peer);
		}
		else
		{
			enet_peer_reset(enetPeer);
			return false;
		}
	}

	//Log: Connected to address/port
	return true;
}

void TE::Network::Host::SendPacketQues()
{
	std::unordered_map<unsigned, PacketQue>::iterator iter = m_packetQuesOut.begin();

	Packet tmpPacket;
	for(; iter != m_packetQuesOut.end(); ++iter)
	{
		iter->second.Pack(tmpPacket);
		ENetPacket *enetPacket = enet_packet_create (tmpPacket.GetBuffer(), tmpPacket.GetLength(), ENET_PACKET_FLAG_RELIABLE);

		if (iter->first == 0)
			enet_host_broadcast(m_host, 0, enetPacket);
		else
			enet_peer_send (m_peers.GetPeer(iter->first).GetEnetPeer(), 0, enetPacket);
	}

	enet_host_flush (m_host);
}
