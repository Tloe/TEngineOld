#ifndef TECRYPTO_H
#define TECRYPTO_H

#include <string>

namespace TE {
namespace Resources {
    class Crypto {
      public:
        virtual ~Crypto(){};
        virtual void Encrypt(char &c) = 0;
        virtual void Decrypt(char &c) = 0;
    };

    class CeasarSipherCrypto : public Crypto {
      public:
        explicit CeasarSipherCrypto(I32 shiftNumber)
            : m_shiftNumber(shiftNumber) {
        }

        void Encrypt(char &c) {
            c += m_shiftNumber;
        }

        void Decrypt(char &c) {
            c -= m_shiftNumber;
        }

      private:
        I32 m_shiftNumber;
    };
}
}

#endif
