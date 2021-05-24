#ifndef TEDATATYPES_H
#define TEDATATYPES_H

#include <cmath>
#include <cstdint>
#include <string>

using I8        = std::int8_t;
using I16       = std::int16_t;
using I32       = std::int32_t;
using I64       = std::int64_t;

using U8        = std::uint8_t;
using U16       = std::uint16_t;
using U32       = std::uint32_t;
using U64       = std::uint64_t;

using F32       = std::float_t;
using F64       = std::double_t;

using ID        = U32;
using Enum      = I32;
using Real      = F32;
using Bitmask   = U32;
using Bitmask64 = U64;

using Hash      = std::size_t;

namespace TE {
    struct HashGenerator {
        Hash operator()(const std::string &filePath) { return s_hasher(filePath); }
        static std::hash<std::string> s_hasher;
    };
}

namespace TYPES {
    enum {
        I8,
        I16,
        I32,
        I64,

        U8,
        U16,
        U32,
        U64,

        F32,
        F64,

        ID,
        Enum,
        Real,
        Bitmask,

        Hash
    };
}

#endif
