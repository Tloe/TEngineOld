#ifndef TEDATATYPES_H
#define TEDATATYPES_H

#include <string>
#include <cstdint>
#include <cmath>

typedef std::int8_t I8;
typedef std::int16_t I16;
typedef std::int32_t I32;
typedef std::int64_t I64;

typedef std::uint8_t U8;
typedef std::uint16_t U16;
typedef std::uint32_t U32;
typedef std::uint64_t U64;

typedef std::float_t F32;
typedef std::double_t F64;

typedef U32 ID;
typedef I32 Enum;
typedef F32 Real;
typedef U32 Bitmask;
typedef U64 Bitmask64;

typedef std::size_t Hash;

namespace TE
{
	struct HashGenerator
	{
		Hash operator()(const std::string& filePath)
		{
			return s_hasher(filePath);
		}
		static std::hash<std::string> s_hasher;
	};
}

namespace TYPES
{
	enum
	{
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
