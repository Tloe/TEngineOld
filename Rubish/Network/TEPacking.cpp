#include <TEPacking.h>
#include <string.h>

void TE::Network::Packet::ExpandBuffer(I32 bits)
{
	if (bits < 1) throw std::out_of_range("bits must be greater than 0");
	
	while ((bitIndex + bits + 7) / 8 > static_cast<I32>(buffer.size())) 
	{
		buffer.push_back(0);
	}

	maxBitIndex = std::max<I32>(maxBitIndex, bitIndex + bits);
}

TE::Network::Packet::Packet()
{
	bitIndex = 0;
	maxBitIndex = 0;
}

TE::Network::Packet::Packet(U8* buffer, I32 maxBitIndex)
{
	bitIndex = 0;
	this->maxBitIndex = maxBitIndex;
	
	this->buffer.resize((maxBitIndex + 7) / 8);
	
	memcpy(&this->buffer[0], buffer, (maxBitIndex + 7) / 8);
}

I32 TE::Network::Packet::GetBitIndex() const
{
	return bitIndex;
}

void TE::Network::Packet::SetBitIndex(I32 value)
{
	if (value < 0 || (value + 7) / 8 > static_cast<I32>(buffer.size()))
	{
		throw std::out_of_range("Unable to set the bit index outside of the buffer size.");
	}
	
	bitIndex = value;
}

I32 TE::Network::Packet::GetMaxBitIndex() const
{
	return maxBitIndex;
}

void TE::Network::Packet::SetMaxBitIndex(I32 value)
{
	if (value < 0 || (value + 7) / 8 > static_cast<I32>(buffer.size()))
	{
		throw std::out_of_range("Unable to set the max bit index outside of the buffer size.");
	}
	maxBitIndex = value;
}

I32 TE::Network::Packet::GetHeaderSize() const
{
	return sizeof(U32);
}

I32 TE::Network::Packet::GetHeaderSizeInBits() const
{
	return sizeof(U32) * 8;
}

I32 TE::Network::Packet::GetLength() const
{
	return static_cast<I32>(buffer.size());
}

const char* TE::Network::Packet::GetBuffer()
{
	return reinterpret_cast<char*>(&buffer[0]);
}

std::string TE::Network::Packet::Trace() const
{
	std::string s = "";
	for (I32 copyBits = 0; copyBits < static_cast<I32>(buffer.size() * 8); ++copyBits)
	{
		s += ((buffer[copyBits / 8] >> (7 - copyBits % 8)) & 0x1) == 0 ? "0" : "1";
		if ((copyBits + 1) % 4 == 0 && copyBits != 0)
		{
			s += " ";
			if ((copyBits + 1) % 8 == 0)
			{
				s += " ";
			}
		}
	}
	return s;
}

void TE::Network::Packet::RoundUpToByte()
{
	bitIndex = (bitIndex + 7) / 8 * 8;
}

void TE::Network::Packet::ReadLength()
{
	I32 oldBitIndex = bitIndex;
	bitIndex = 0;
	maxBitIndex = 0;
	U32 length;
	if (ReadUint32(length))
	{
		maxBitIndex = static_cast<I32>(length);
	}
	bitIndex = oldBitIndex;
}

void TE::Network::Packet::BeginPacket()
{
	WriteUint32(0);
}

void TE::Network::Packet::EndPacket()
{
	I32 oldBitIndex = bitIndex;
	bitIndex = 0;
	WriteUint32(static_cast<U32>(maxBitIndex));
	bitIndex = oldBitIndex;
}

// Write Methods

void TE::Network::Packet::WriteEventID(U32 value)
{
	WriteDynamicUint(value, 6);
}

void TE::Network::Packet::WriteBool(bool value)
{
	ExpandBuffer(1);
	if (value) buffer[bitIndex / 8] |= static_cast<U8>(1 << (7 - bitIndex % 8));
	++bitIndex;
}

void TE::Network::Packet::WriteByte(U8 value)
{
	ExpandBuffer(8);
	I32 offset = bitIndex % 8;
	buffer[bitIndex / 8] |= value >> offset;
	if (offset != 0)
	{
		buffer[bitIndex / 8 + 1] |= value << (8 - offset);
	}
	bitIndex += 8;
}

void TE::Network::Packet::WriteSByte(I8 value)
{
	ExpandBuffer(8);
	I32 offset = bitIndex % 8;
	buffer[bitIndex / 8] |= value >> offset;
	if (offset != 0)
	{
		buffer[bitIndex / 8 + 1] |= value << (8 - offset);
	}

	bitIndex += 8;
}

void TE::Network::Packet::WriteUint16(U16 value)
{
	ExpandBuffer(16);
	I32 offset = bitIndex % 8;
	buffer[bitIndex / 8] |= value >> (8 + offset);
	buffer[bitIndex / 8 + 1] |= value >> offset;
	if (offset != 0)
	{
		buffer[bitIndex / 8 + 2] |= value << (8 - offset);
	}
	bitIndex += 16;
}

void TE::Network::Packet::Writeint16(I16 value)
{
	ExpandBuffer(16);
	I32 offset = bitIndex % 8;
	buffer[bitIndex / 8] |= value >> (8 + offset);
	buffer[bitIndex / 8 + 1] |= value >> offset;
	if (offset != 0)
	{
		buffer[bitIndex / 8 + 2] |= value << (8 - offset);
	}
	bitIndex += 16;
}

void TE::Network::Packet::WriteUint32(U32 value)
{
	ExpandBuffer(32);
	I32 offset = bitIndex % 8;
	buffer[bitIndex / 8] |= value >> (24 + offset);
	buffer[bitIndex / 8 + 1] |= value >> (16 + offset);
	buffer[bitIndex / 8 + 2] |= value >> (8 + offset);
	buffer[bitIndex / 8 + 3] |= value >> offset;
	if (offset != 0)
	{
		buffer[bitIndex / 8 + 4] |= value << (8 - offset);
	}
	bitIndex += 32;
}

void TE::Network::Packet::Writeint32(I32 value)
{
	ExpandBuffer(32);
	I32 offset = bitIndex % 8;
	buffer[bitIndex / 8] |= value >> (24 + offset);
	buffer[bitIndex / 8 + 1] |= value >> (16 + offset);
	buffer[bitIndex / 8 + 2] |= value >> (8 + offset);
	buffer[bitIndex / 8 + 3] |= value >> offset;
	if (offset != 0)
	{
		buffer[bitIndex / 8 + 4] |= value << (8 - offset);
	}
	bitIndex += 32;
}

void TE::Network::Packet::WriteUint(U32 value, I32 bits)
{
	if (bits < 1 || bits > 32) throw std::out_of_range("bits must be in the range (0, 32].");
	if (bits != 32 && value > static_cast<U32>((0x1 << bits) - 1))
	{
		std::ostringstream exceptionStr;
		exceptionStr << "Value does not fit into " << bits << " bits.";
		throw std::out_of_range(exceptionStr.str());
	}

	ExpandBuffer(bits);

	value <<= 32 - bits;

	I32 offset = bitIndex % 8;
	buffer[bitIndex / 8] |= value >> (24 + offset);
	if (offset + bits > 8)
	{
		buffer[bitIndex / 8 + 1] |= value >> (16 + offset);
		if (offset + bits > 16)
		{
			buffer[bitIndex / 8 + 2] |= value >> (8 + offset);
			if (offset + bits > 24)
			{
				buffer[bitIndex / 8 + 3] |= value >> offset;
				if (offset + bits > 32)
				{
					buffer[bitIndex / 8 + 4] |= value << (8 - offset);
				}
			}
		}
	}
	bitIndex += bits;
}

void TE::Network::Packet::Writeint(I32 value, I32 bits)
{
	if (bits < 1 || bits > 32) throw std::out_of_range("bits must be in the range (0, 32].");
	if (bits != 32 && (value < -(0x1 << (bits - 1)) || value >= 0x1 << (bits - 1)))
	{
		std::ostringstream exceptionStr;
		exceptionStr << "Value does not fit into " << bits << " bits.";
		throw std::out_of_range(exceptionStr.str());
	}

	ExpandBuffer(bits);

	value <<= 32 - bits;
	U32 uvalue = *reinterpret_cast<U32*>(&value);

	I32 offset = bitIndex % 8;
	buffer[bitIndex / 8] |= uvalue >> (24 + offset);
	if (offset + bits > 8)
	{
		buffer[bitIndex / 8 + 1] |= uvalue >> (16 + offset);
		if (offset + bits > 16)
		{
			buffer[bitIndex / 8 + 2] |= uvalue >> (8 + offset);
			if (offset + bits > 24)
			{
				buffer[bitIndex / 8 + 3] |= uvalue >> offset;
				if (offset + bits > 32)
				{
					buffer[bitIndex / 8 + 4] |= uvalue << (8 - offset);
				}
			}
		}
	}
	bitIndex += bits;
}

void TE::Network::Packet::WriteF32(F32 value)
{
	WriteUint32(*reinterpret_cast<U32*>(&value));
}

void TE::Network::Packet::WriteDouble(F64 value)
{
	U32* ints = reinterpret_cast<U32*>(&value);
	WriteUint32(ints[0]);
	WriteUint32(ints[1]);
}

void TE::Network::Packet::WriteDynamicUint(U32 value, I32 bits)
{
	if (bits < 1 || bits > 32) throw std::out_of_range("bits must be in the range (0, 32].");
	I32 shift = bits;
	// Stop when our value can fit inside
	for (; shift < 32 && value >= static_cast<U32>(0x1 << shift); shift += bits)
	{
		WriteBool(true);  // Write a 1 for a continuation bit signifying one more interval is needed
	}
	if (shift < 32)
	{
		WriteBool(false); // Write a 0 for a continuation bit signifying the end
	}
	WriteUint(value, shift >= 32 ? 32 : shift);
}

void TE::Network::Packet::WriteDynamicUint(U32 value)
{
	WriteDynamicUint(value, 4);
}

void TE::Network::Packet::WriteDynamicint(I32 value, I32 bits)
{
	if (bits < 1 || bits > 32) throw std::out_of_range("bits must be in the range (0, 32].");
	I32 shift = bits;
	// Stop when our value can fit inside
	for (; shift < 32 && (value < -(0x1 << (shift - 1)) || value >= 0x1 << (shift - 1)); shift += bits)
	{
		WriteBool(true);  // Write a 1 for a continuation bit signifying one more interval is needed
	}
	if (shift < 32)
	{
		WriteBool(false); // Write a 0 for a continuation bit signifying the end
	}
	Writeint(value, shift >= 32 ? 32 : shift);
}

void TE::Network::Packet::WriteDynamicint(I32 value)
{
	WriteDynamicint(value, 4);
}

void TE::Network::Packet::WriteCustomResolutionF32(F32 value, F32 min, F32 max, I32 bitResolution)
{
	if (bitResolution < 1 || bitResolution > 31) throw std::out_of_range("bitResolution must be in the range (0, 32).");
	if (min > max) throw std::out_of_range("min argument must be less than the max argument.");
	if (value < min || value > max) throw std::out_of_range("The value must be on the interval [min, max]");
	U32 uValue;
	if (min < 0 && max > 0)
	{
		uValue = value == 0 ? 0 : static_cast<U32>((value - min) / (max - min) * static_cast<F32>((0x1 << bitResolution) - 2) + 0.5) + 1;
	}
	else
	{
		uValue = static_cast<U32>((value - min) / (max - min) * static_cast<F32>((0x1 << bitResolution) - 1) + 0.5);
	}
	WriteUint(uValue, bitResolution);
}

void TE::Network::Packet::WriteCustomResolutionDouble(F64 value, F64 min, F64 max, I32 bitResolution)
{
	if (bitResolution < 1 || bitResolution > 31) throw std::out_of_range("bitResolution must be in the range (0, 32).");
	if (min > max) throw std::out_of_range("min argument must be less than the max argument.");
	if (value < min || value > max) throw std::out_of_range("The value must be on the interval [min, max]");
	U32 uValue;
	if (min < 0 && max > 0)
	{
		uValue = value == 0 ? 0 : static_cast<U32>((value - min) / (max - min) * static_cast<F64>((0x1 << bitResolution) - 2) + 0.5) + 1;
	}
	else
	{
		uValue = static_cast<U32>((value - min) / (max - min) * static_cast<F64>((0x1 << bitResolution) - 1) + 0.5);
	}
	WriteUint(uValue, bitResolution);
}

void TE::Network::Packet::WriteString(const std::string& value, I32 bits)
{
	if (bits < 1 || bits > 31) throw std::out_of_range("bits must be in the range (0, 32).");
	U32 size = static_cast<U32>(value.length());
	WriteDynamicUint(size, bits);
	for (std::string::const_iterator strItr = value.begin(); strItr != value.end(); ++strItr)
	{
		WriteByte(*strItr);
	}
}

void TE::Network::Packet::WriteString(const std::string& value)
{
	WriteString(value, 4);
}

void TE::Network::Packet::WriteBinaryPacket(const Packet& value)
{
	I32 valueBitIndex = 0;
	I32 valueMaxBitIndex = value.maxBitIndex;
	WriteDynamicUint(static_cast<U32>(valueMaxBitIndex));
	for (I32 copyBytes = 0; copyBytes < valueMaxBitIndex / 8; ++copyBytes)
	{
		U8 valueByte = 0;
		if ((valueBitIndex + 8 + 7) / 8 >= static_cast<I32>(value.buffer.size()))
		{
			I32 offset = valueBitIndex % 8;
			valueByte |= value.buffer[valueBitIndex / 8] << offset;
			if (offset != 0)
			{
				valueByte |= value.buffer[valueBitIndex / 8 + 1] >> (8 - offset);
			}
		}
		valueBitIndex += 8;
		WriteByte(valueByte);
	}
	for (I32 copyBits = 0; copyBits < valueMaxBitIndex % 8; ++copyBits)
	{
		bool valueBit = false;
		if ((valueBitIndex + 1 + 7) / 8 <= static_cast<I32>(value.buffer.size()))
		{
			valueBit = ((value.buffer[valueBitIndex / 8] >> (7 - valueBitIndex % 8)) & 0x1) == 1;
		}
		++valueBitIndex;
		WriteBool(valueBit);
	}
	bitIndex += valueMaxBitIndex;
}

// Read Methods

bool TE::Network::Packet::ReadEventID(U32& value)
{
	return ReadDynamicUint(value, 6);
}

bool TE::Network::Packet::ReadBool(bool& value)
{
	value = false;
	if ((bitIndex + 1 + 7) / 8 > static_cast<I32>(buffer.size()))
	{
		return false;
	}
	value = ((buffer[bitIndex / 8] >> (7 - bitIndex % 8)) & 0x1) == 1;
	++bitIndex;
	return true;
}

bool TE::Network::Packet::ReadByte(U8& value)
{
	value = 0;
	if ((bitIndex + 8 + 7) / 8 > static_cast<I32>(buffer.size()))
	{
		return false;
	}
	I32 offset = bitIndex % 8;
	value |= buffer[bitIndex / 8] << offset;
	if (offset != 0)
	{
		value |= buffer[bitIndex / 8 + 1] >> (8 - offset);
	}
	bitIndex += 8;
	return true;
}

bool TE::Network::Packet::ReadSByte(I8& value)
{
	value = 0;
	if ((bitIndex + 8 + 7) / 8 > static_cast<I32>(buffer.size()))
	{
		return false;
	}
	I32 offset = bitIndex % 8;
	value |= buffer[bitIndex / 8] << offset;
	if (offset != 0)
	{
		value |= buffer[bitIndex / 8 + 1] >> (8 - offset);
	}
	bitIndex += 8;
	return true;
}

bool TE::Network::Packet::ReadUint16(U16& value)
{
	value = 0;
	if ((bitIndex + 16 + 7) / 8 > static_cast<I32>(buffer.size()))
	{
		return false;
	}
	I32 offset = bitIndex % 8;
	value |= buffer[bitIndex / 8] << (8 + offset);
	value |= buffer[bitIndex / 8 + 1] << offset;
	if (offset != 0)
	{
		value |= buffer[bitIndex / 8 + 2] >> (8 - offset);
	}
	bitIndex += 16;
	return true;
}

bool TE::Network::Packet::Readint16(I16& value)
{
	value = 0;
	if ((bitIndex + 16 + 7) / 8 > static_cast<I32>(buffer.size()))
	{
		return false;
	}
	I32 offset = bitIndex % 8;
	value |= buffer[bitIndex / 8] << (8 + offset);
	value |= buffer[bitIndex / 8 + 1] << offset;
	if (offset != 0)
	{
		value |= buffer[bitIndex / 8 + 2] >> (8 - offset);
	}
	bitIndex += 16;
	return true;
}

bool TE::Network::Packet::ReadUint32(U32& value)
{
	value = 0;
	if ((bitIndex + 32 + 7) / 8 > static_cast<I32>(buffer.size()))
	{
		return false;
	}
	I32 offset = bitIndex % 8;
	value |= buffer[bitIndex / 8] << (24 + offset);
	value |= buffer[bitIndex / 8 + 1] << (16 + offset);
	value |= buffer[bitIndex / 8 + 2] << (8 + offset);
	value |= buffer[bitIndex / 8 + 3] << offset;
	if (offset != 0)
	{
		value |= buffer[bitIndex / 8 + 4] >> (8 - offset);
	}
	bitIndex += 32;
	return true;
}

bool TE::Network::Packet::Readint32(I32& value)
{
	value = 0;
	if ((bitIndex + 32 + 7) / 8 > static_cast<I32>(buffer.size()))
	{
		return false;
	}
	I32 offset = bitIndex % 8;
	value |= buffer[bitIndex / 8] << (24 + offset);
	value |= buffer[bitIndex / 8 + 1] << (16 + offset);
	value |= buffer[bitIndex / 8 + 2] << (8 + offset);
	value |= buffer[bitIndex / 8 + 3] << offset;
	if (offset != 0)
	{
		value |= buffer[bitIndex / 8 + 4] >> (8 - offset);
	}
	bitIndex += 32;
	return true;
}

bool TE::Network::Packet::ReadUint(U32& value, I32 bits)
{
	if (bits < 1 || bits > 32) throw std::out_of_range("bits must be in the range (0, 32].");

	value = 0;
	if ((bitIndex + bits + 7) / 8 > static_cast<I32>(buffer.size()))
	{
		return false;
	}

	I32 offset = bitIndex % 8;
	value = buffer[bitIndex / 8] << (24 + offset);
	if (offset + bits > 8)
	{
		value |= buffer[bitIndex / 8 + 1] << (16 + offset);
		if (offset + bits > 16)
		{
			value |= buffer[bitIndex / 8 + 2] << (8 + offset);
			if (offset + bits > 24)
			{
				value |= buffer[bitIndex / 8 + 3] << offset;
				if (offset + bits > 32)
				{
					value |= buffer[bitIndex / 8 + 4] >> (8 - offset);
				}
			}
		}
	}

	value >>= 32 - bits;
	bitIndex += bits;
	return true;
}

bool TE::Network::Packet::Readint(I32& value, I32 bits)
{
	if (bits < 1 || bits > 32) throw std::out_of_range("bits must be in the range (0, 32].");

	value = 0;
	if ((bitIndex + bits + 7) / 8 > static_cast<I32>(buffer.size()))
	{
		return false;
	}

	I32 offset = bitIndex % 8;
	value = buffer[bitIndex / 8] << (24 + offset);
	if (offset + bits > 8)
	{
		value |= buffer[bitIndex / 8 + 1] << (16 + offset);
		if (offset + bits > 16)
		{
			value |= buffer[bitIndex / 8 + 2] << (8 + offset);
			if (offset + bits > 24)
			{
				value |= buffer[bitIndex / 8 + 3] << offset;
				if (offset + bits > 32)
				{
					value |= buffer[bitIndex / 8 + 4] >> (8 - offset);
				}
			}
		}
	}

	value >>= 32 - bits;
	bitIndex += bits;
	return true;
}

bool TE::Network::Packet::ReadSingle(F32& value)
{
	value = 0;
	if ((bitIndex + 32 + 7) / 8 > (I32)buffer.size())
	{
		return false;
	}
	U32 uValue;
	if (!ReadUint32(uValue)) return false;
	value = *reinterpret_cast<F32*>(&uValue);
	return true;
}

bool TE::Network::Packet::ReadDouble(F64& value)
{
	value = 0;
	if ((bitIndex + 64 + 7) / 8 > (I32)buffer.size())
	{
		return false;
	}
	U32 ints[2];
	if (!ReadUint32(ints[0])) return false;
	if (!ReadUint32(ints[1])) return false;
	value = *reinterpret_cast<F64*>(ints);
	return true;
}

bool TE::Network::Packet::ReadDynamicUint(U32& value, I32 bits)
{
	if (bits < 1 || bits > 32) throw std::out_of_range("bits must be in the range (0, 32].");
	value = 0;
	I32 valueBitCount = bits;
	bool continuationBitValue = true;
	do
	{
		if (!ReadBool(continuationBitValue)) return false;
		if (continuationBitValue) valueBitCount += bits;
	}
	while (continuationBitValue && valueBitCount < 32);
	return ReadUint(value, valueBitCount >= 32 ? 32 : valueBitCount);
}

bool TE::Network::Packet::ReadDynamicUint(U32& value)
{
	return ReadDynamicUint(value, 4);
}

bool TE::Network::Packet::ReadDynamicint(I32& value, I32 bits)
{
	if (bits < 1 || bits > 32) throw std::out_of_range("bits must be in the range (0, 32].");
	value = 0;
	I32 valueBitCount = bits;
	bool continuationBitValue = true;
	do
	{
		if (!ReadBool(continuationBitValue)) return false;
		if (continuationBitValue) valueBitCount += bits;
	}
	while (continuationBitValue && valueBitCount < 32);
	return Readint(value, valueBitCount >= 32 ? 32 : valueBitCount);
}

bool TE::Network::Packet::ReadDynamicint(I32& value)
{
	return ReadDynamicint(value, 4);
}

bool TE::Network::Packet::ReadCustomResolutionSingle(F32& value, F32 min, F32 max, I32 bitResolution)
{
	if (bitResolution < 1 || bitResolution > 31) throw std::out_of_range("bitResolution must be in the range (0, 32).");
	if (min > max) throw std::out_of_range("min argument must be less than the max argument.");
	value = 0;
	U32 uValue;
	if (!ReadUint(uValue, bitResolution)) return false;
	if (min < 0 && max > 0)
	{
		value = uValue == 0 ? 0 : (uValue - 1) / static_cast<F32>((0x1 << bitResolution) - 2) * (max - min) + min;
	}
	else
	{
		value = uValue / static_cast<F32>((0x1 << bitResolution) - 1) * (max - min) + min;
	}
	return true;
}

bool TE::Network::Packet::ReadCustomResolutionDouble(F64& value, F64 min, F64 max, I32 bitResolution)
{
	if (bitResolution < 1 || bitResolution > 31) throw std::out_of_range("bitResolution must be in the range (0, 32).");
	if (min > max) throw std::out_of_range("min argument must be less than the max argument.");
	value = 0;
	U32 uValue;
	if (!ReadUint(uValue, bitResolution)) return false;
	if (min < 0 && max > 0)
	{
		value = uValue == 0 ? 0 : (uValue - 1) / static_cast<F64>((0x1 << bitResolution) - 2) * (max - min) + min;
	}
	else
	{
		value = uValue / static_cast<F64>((0x1 << bitResolution) - 1) * (max - min) + min;
	}
	return true;
}

bool TE::Network::Packet::ReadString(std::string& value, I32 bits)
{
	if (bits < 1 || bits > 31) throw std::out_of_range("bits must be in the range (0, 32).");
	value = "";
	U32 size;
	if (!ReadDynamicUint(size, bits)) return false;
	for (U32 strItr = 0; strItr < size; ++strItr)
	{
		U8 c;
		if (!ReadByte(c)) return false;
		value += c;
	}
	return true;
}

bool TE::Network::Packet::ReadString(std::string& value)
{
	return ReadString(value, 4);
}

bool TE::Network::Packet::ReadBinaryPacket(TE::Network::Packet& value)
{
	U32 valueMaxBitIndex;
	if (!ReadDynamicUint(valueMaxBitIndex)) return false;
	for (U32 copyBytes = 0; copyBytes < valueMaxBitIndex / 8; ++copyBytes)
	{
		U8 valueByte;
		if (!ReadByte(valueByte)) return false;
		value.WriteByte(valueByte);
	}
	for (U32 copyBits = 0; copyBits < valueMaxBitIndex % 8; ++copyBits)
	{
		bool valueBit;
		if (!ReadBool(valueBit)) return false;
		value.WriteBool(valueBit);
	}
	bitIndex += (I32)valueMaxBitIndex;
	value.bitIndex = 0;
	return true;
}
