#include "TEAddress.h"
#include <assert.h>
#include <sstream>
#include <string.h>

TE::Net::Address::Address() {
}

TE::Net::Address::Address(sockaddr_storage &sockaddres)
    : m_address(sockaddres) {
}

TE::Net::Address::Address(const std::string &addressStr, const std::string &port, IPFamily ipFamily) {
    SetAddress(addressStr, port, ipFamily);
}

TE::Net::Address::Address(const Address &other)
    : m_address(other.m_address) {
}

bool TE::Net::Address::operator==(const Address &other) const {
    if (m_address.ss_family != other.m_address.ss_family) {
        return false;
    }

    if (m_address.ss_family == AF_INET) {
        const sockaddr_in *pLhs = reinterpret_cast<const sockaddr_in *>(&m_address);
        const sockaddr_in *pRhs = reinterpret_cast<const sockaddr_in *>(&other.m_address);
        return pLhs->sin_addr.s_addr == pRhs->sin_addr.s_addr &&
               pLhs->sin_port == pRhs->sin_port;
    } else {
        const sockaddr_in6 *pLhs = reinterpret_cast<const sockaddr_in6 *>(&m_address);
        const sockaddr_in6 *pRhs = reinterpret_cast<const sockaddr_in6 *>(&other.m_address);
        return pLhs->sin6_addr.s6_addr == pRhs->sin6_addr.s6_addr &&
               pLhs->sin6_port == pRhs->sin6_port;
    }
}

bool TE::Net::Address::operator!=(const Address &other) const {
    return !(*this == other);
}

bool TE::Net::Address::operator<(const TE::Net::Address &other) const {
    if (m_address.ss_family == AF_INET) {
        const sockaddr_in *pLhs = reinterpret_cast<const sockaddr_in *>(&m_address);
        const sockaddr_in *pRhs = reinterpret_cast<const sockaddr_in *>(&other.m_address);
        if (pLhs->sin_port < pRhs->sin_port)
            return true;

        return pLhs->sin_addr.s_addr < pRhs->sin_addr.s_addr;
    } else {
        const sockaddr_in6 *pLhs = reinterpret_cast<const sockaddr_in6 *>(&m_address);
        const sockaddr_in6 *pRhs = reinterpret_cast<const sockaddr_in6 *>(&other.m_address);

        if (pLhs->sin6_port < pRhs->sin6_port)
            return true;

        return pLhs->sin6_addr.s6_addr < pRhs->sin6_addr.s6_addr;
    }
}

void TE::Net::Address::SetAddress(sockaddr_storage &sockaddres) {
    m_address = sockaddres;
}

void TE::Net::Address::SetAddress(const std::string &addressStr, const std::string &port, IPFamily ipFamily) {
    addrinfo *address;
    addrinfo addressHints;
    memset(&addressHints, 0, sizeof(addressHints));
    addressHints.ai_family   = ipFamily == IPFamily::IPv4 ? AF_INET : AF_INET6;
    addressHints.ai_socktype = SOCK_DGRAM;
    int test                 = getaddrinfo(addressStr.c_str(), port.c_str(), &addressHints, &address);
    if (test != 0) {
        // LOG critical
        exit(1);
    }
    m_address = *reinterpret_cast<sockaddr_storage *>(address->ai_addr);
}

const sockaddr_storage &TE::Net::Address::GetSockaddrStorage() const {
    return m_address;
}

void TE::Net::Address::GetAddress(std::string &address, std::string &port) {
    std::stringstream ssPort;
    switch (m_address.ss_family) {
    case AF_INET:
        char buffer4[INET_ADDRSTRLEN];
        inet_ntop(AF_INET,
                  &(reinterpret_cast<sockaddr_in *>(&m_address)->sin_addr),
                  buffer4,
                  INET_ADDRSTRLEN);
        address = buffer4;
        ssPort << ntohs(reinterpret_cast<const sockaddr_in *>(&m_address)->sin_port);
        port = ssPort.str();
        break;
    case AF_INET6:
        char buffer6[INET6_ADDRSTRLEN];
        inet_ntop(AF_INET6,
                  &(reinterpret_cast<sockaddr_in6 *>(&m_address)->sin6_addr),
                  buffer6,
                  INET6_ADDRSTRLEN);
        address = buffer6;
        ssPort << ntohs(reinterpret_cast<const sockaddr_in6 *>(&m_address)->sin6_port);
        port = ssPort.str();
        break;
    default:
        assert(false && "Should never get here!");
    }
}
