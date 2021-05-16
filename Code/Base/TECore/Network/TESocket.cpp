#include "TESocket.h"
#include "TEAddress.h"
#include "TEPacket.h"

#include <assert.h>
#include <cstring>
#include <iostream>

#if TE_WINDOWS
typedef int socklen_t;
#endif

namespace {
    enum { MaxPacketSize = 64000 };

    void CloseSocket(I32 &socket) {
#if TE_WINDOWS
        closesocket(socket);
#elif TE_LINUX
        close(socket);
#endif
        socket = 0;
    }

    // set non-blocking io
    bool SetNonblockingIO(I32 socket) {
#if TE_WINDOWS
        DWORD nonBlocking = 1;
        if (ioctlsocket(socket, FIONBIO, &nonBlocking) != 0) {
            return false;
        }
#elif TE_LINUX
        int nonBlocking = 1;
        if (fcntl(socket, F_SETFL, O_NONBLOCK, nonBlocking) == -1) {
            return false;
        }
#endif
        return true;
    }

    void AssertPacketNotToLong() {
#if TE_WINDOWS
        assert(WSAGetLastError() != WSAEMSGSIZE && "packet to long");
#elif TE_LINUX
        assert(errno != EMSGSIZE && "packet to long");
#endif
    }

    bool CompareBufferProtocolId(std::vector<U8> buffer, I32 bytesInBuffer, I32 bitIndex, U16 protocolId) {
        if ((bitIndex + 16 + 7) / 8 > bytesInBuffer)
            return false;

        I32 offset = bitIndex % 8;
        U16 value  = 0;
        value |= buffer[bitIndex / 8] << (8 + offset);
        value |= buffer[bitIndex / 8 + 1] << offset;
        if (offset != 0) {
            value |= buffer[bitIndex / 8 + 2] >> (8 - offset);
        }

        return value == protocolId;
    }
}

TE::Net::Socket::Socket(U16 protocolId)
    : m_protocolId(protocolId),
      m_socket(0) {
    m_receiveBuffer.resize(MaxPacketSize);
}

TE::Net::Socket::~Socket() {
    Close();
}

bool TE::Net::Socket::Open(const std::string &port, IPFamily ipFamily) {
    assert(!IsOpen());

    debugPort = port;

    // create socket
    addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = (ipFamily == IPFamily::IPv4) ? AF_INET : AF_INET6;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags    = AI_PASSIVE;

    addrinfo *addressInfo;
    if (getaddrinfo(nullptr, port.c_str(), &hints, &addressInfo) != 0) {
        assert(false);
        // LOG critical error
        exit(0);
    }

    for (auto ptr = addressInfo; ptr != nullptr; ptr = ptr->ai_next) {
        if ((m_socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol)) == -1) {
            m_socket = 0;
            continue;
        }

        char yes = 1;
        if (setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(I32)) == -1) {
            Close();
            continue;
        }

        if (bind(m_socket, ptr->ai_addr, ptr->ai_addrlen) == -1) {
            Close();
            continue;
        }

        break;
    }

    freeaddrinfo(addressInfo);

    if (m_socket <= 0) {
        assert(false);
        // LOG critical error
        exit(0);
    }

    if (!::SetNonblockingIO(m_socket)) {
        assert(false);
        // LOG critical error
        exit(0);
    }

    return true;
}

void TE::Net::Socket::Close() {
    if (m_socket != 0) {
        ::CloseSocket(m_socket);
    }
}

bool TE::Net::Socket::IsOpen() const {
    return m_socket != 0;
}

bool TE::Net::Socket::SendTo(const Address &address, Packet &packet) {
    if (m_socket == 0)
        return false;

    packet.WritePacketId(m_protocolId);

    socklen_t sockaddrLenght = (address.GetSockaddrStorage().ss_family == AF_INET) ? INET_ADDRSTRLEN : INET6_ADDRSTRLEN;

    assert(packet.IsStartedAndEnded() && "Packet is not valid!");
    int sent_bytes = sendto(m_socket,
                            packet.GetBuffer(),
                            packet.GetLength(),
                            0,
                            reinterpret_cast<const sockaddr *>(&address.GetSockaddrStorage()),
                            sockaddrLenght);

    ::AssertPacketNotToLong();

    return sent_bytes == packet.GetLength();
}

bool TE::Net::Socket::GetReceivedPacketFrom(const Address &address, Packet &packet) {
    auto findItr = m_receivedPackets.find(address);
    if (findItr == m_receivedPackets.end() || findItr->second.empty())
        return false;

    packet = findItr->second.front();

    findItr->second.pop_front();

    return true;
}

void TE::Net::Socket::NewConnection(const TE::Net::Address &address) {
    m_receivedPackets.insert(std::make_pair(address, PacketList()));
}

bool TE::Net::Socket::HasIncomingConnection(TE::Net::Address &address) {
    if (m_newIncomming.empty())
        return false;

    address = m_newIncomming.front();
    m_newIncomming.pop_front();

    return true;
}

void TE::Net::Socket::ConnectionTimeout(const TE::Net::Address &address) {
    m_receivedPackets.erase(address);
}

void TE::Net::Socket::Update() {
    assert(m_socket != 0 && "Socket not opened yet");

    I32 receivedBytes = 1;
    sockaddr_storage sockAddress;
    socklen_t addressSize = sizeof(sockAddress);
    while (receivedBytes > 0) {
        receivedBytes = recvfrom(m_socket,
                                 reinterpret_cast<char *>(&m_receiveBuffer[0]),
                                 MaxPacketSize,
                                 0,
                                 reinterpret_cast<sockaddr *>(&sockAddress),
                                 &addressSize);

        if (receivedBytes > 0 && ::CompareBufferProtocolId(m_receiveBuffer, receivedBytes, PacketHeader::BitIndex::PacketId, m_protocolId)) {
            Packet packet;
            packet.SetPacketBuffer(reinterpret_cast<U8 *>(&m_receiveBuffer[0]), receivedBytes);
            Address address;
            address.SetAddress(sockAddress);

            auto findItr = m_receivedPackets.find(address);
            if (findItr == m_receivedPackets.end()) {
                m_newIncomming.push_front(address);
            }
            m_receivedPackets[address].push_back(std::move(packet));
        }
    }
}

bool TE::Net::InitializeSockets() {
#if TE_WINDOWS
    WSADATA WsaData;
    return WSAStartup(MAKEWORD(2, 2), &WsaData) == NO_ERROR;
#endif
    return true;
}

bool TE::Net::CleanupSockets() {
#if TE_WINDOWS
    WSACleanup();
#endif
    return true;
}
