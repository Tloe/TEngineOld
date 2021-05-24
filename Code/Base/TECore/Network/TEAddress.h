#ifndef TEADDRESS_H
#define TEADDRESS_H

#include "TEDataTypes.h"
#include "TESocketIncludes.h"

namespace TE::Net {
    enum class IPFamily { IPv4, IPv6 };

    class Address {
      public:
        Address();
        Address(sockaddr_storage &sockaddres);
        Address(const std::string &addressStr, const std::string &port, IPFamily ipFamily);
        Address(const Address &other);

        bool operator==(const Address &other) const;
        bool operator!=(const Address &other) const;
        bool operator<(const Address &other) const;

        void SetAddress(sockaddr_storage &sockaddres);
        void SetAddress(const std::string &addressStr, const std::string &port, IPFamily ipFamily);

        const sockaddr_storage &GetSockaddrStorage() const;
        void GetAddress(std::string &address, std::string &port);

      private:
        sockaddr_storage m_address;
    };
}

#endif
