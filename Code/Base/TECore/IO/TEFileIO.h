#ifndef TEFILEIO_H
#define TEFILEIO_H

#include "TEDataTypes.h"

#include <stdint.h>
#include <string>
#include <vector>

namespace TE {
namespace IO {
    class FileIO {
      public:
        virtual ~FileIO();
        virtual void LoadFile(const std::string &filePath, std::vector<U8> &data)       = 0;
        virtual void LoadFile(I32 fileHash, std::vector<U8> &data)                      = 0;
        virtual void SaveFile(const std::string &filePath, const std::vector<U8> &data) = 0;
        virtual void SaveFile(I32 fileHash, const std::vector<U8> &data)                = 0;
        virtual bool SupportsHash()                                                     = 0;
    };

    void WriteU32ToU8Vector(U32 u32val, std::vector<U8> &data);
    void ReadU32FromU8Array(U32 &u32val, const U8 *data);
}
}

#endif
