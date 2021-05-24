#include "TEPacket.h"
#include "TEQuaternion.h"
#include "TEVector3D.h"

#include <algorithm>
#include <assert.h>
#include <bitset>
#include <iostream>
#include <string.h>

namespace {
    const U32 packetReadIndex =
        TE::Net::PacketHeader::BitCount::PacketSize + TE::Net::PacketHeader::BitCount::PacketType +
        TE::Net::PacketHeader::BitCount::PacketId + TE::Net::PacketHeader::BitCount::SequenceNo +
        TE::Net::PacketHeader::BitCount::Ack + TE::Net::PacketHeader::BitCount::AckBits;

    const U32 messageReadIndex = TE::Net::PacketHeader::BitCount::PacketSize +
                                 TE::Net::PacketHeader::BitCount::PacketType +
                                 TE::Net::PacketHeader::BitCount::MessageType;

    const U32 packetHeaderSize =
        TE::Net::PacketHeader::ByteCount::PacketSize + TE::Net::PacketHeader::ByteCount::PacketId +
        TE::Net::PacketHeader::ByteCount::SequenceNo + TE::Net::PacketHeader::ByteCount::Ack +
        TE::Net::PacketHeader::ByteCount::AckBits;
    const U32 messageHeaderSize = TE::Net::PacketHeader::ByteCount::PacketSize;
}

TE::Net::Packet::Packet()
    : m_bitIndex(0),
      m_maxBitIndex(0),
      m_packetStarted(false),
      m_packetEnded(false) {}

TE::Net::Packet::Packet(U8 *buffer, U32 size) { SetPacketBuffer(buffer, size); }

void TE::Net::Packet::WriteMessageType(I32 value) {
    assert(GetPacketType() == PacketType::Message);

    I32 oldBitIndex = m_bitIndex;
    m_bitIndex      = PacketHeader::BitIndex::MessageType;
    Reset8Bits();
    m_bitIndex = PacketHeader::BitIndex::MessageType;
    WriteI8(static_cast<I8>(value));
    m_bitIndex = oldBitIndex;
}

void TE::Net::Packet::ReadMessageType(I32 &value) {
    assert(GetPacketType() == PacketType::Message);

    I32 oldBitIndex = m_bitIndex;
    m_bitIndex      = PacketHeader::BitIndex::MessageType;
    I8 temp;
    ReadI8(temp);
    value      = static_cast<I32>(temp);
    m_bitIndex = oldBitIndex;
}

void TE::Net::Packet::WritePacketId(U16 value) {
    assert(GetPacketType() == PacketType::Packet);

    I32 oldBitIndex = m_bitIndex;
    m_bitIndex      = PacketHeader::BitIndex::PacketId;
    WriteU16(value);
    m_bitIndex = oldBitIndex;
}

void TE::Net::Packet::ReadPacketId(U16 &value) {
    assert(GetPacketType() == PacketType::Packet);

    I32 oldBitIndex = m_bitIndex;
    m_bitIndex      = PacketHeader::BitIndex::PacketId;
    ReadU16(value);
    m_bitIndex = oldBitIndex;
}

void TE::Net::Packet::WriteSequenceNo(U32 value) {
    assert(GetPacketType() == PacketType::Packet);

    I32 oldBitIndex = m_bitIndex;
    m_bitIndex      = PacketHeader::BitIndex::SequenceNo;
    Reset32Bits();
    m_bitIndex = PacketHeader::BitIndex::SequenceNo;
    WriteU32(value);
    m_bitIndex = oldBitIndex;
}

void TE::Net::Packet::ReadSequenceNo(U32 &value) {
    assert(GetPacketType() == PacketType::Packet);

    I32 oldBitIndex = m_bitIndex;
    m_bitIndex      = PacketHeader::BitIndex::SequenceNo;
    ReadU32(value);
    m_bitIndex = oldBitIndex;
}

void TE::Net::Packet::WriteAck(U32 value) {
    assert(GetPacketType() == PacketType::Packet);

    I32 oldBitIndex = m_bitIndex;
    m_bitIndex      = PacketHeader::BitIndex::Ack;
    Reset32Bits();
    m_bitIndex = PacketHeader::BitIndex::Ack;
    WriteU32(value);
    m_bitIndex = oldBitIndex;
}

void TE::Net::Packet::ReadAck(U32 &value) {
    assert(GetPacketType() == PacketType::Packet);

    I32 oldBitIndex = m_bitIndex;
    m_bitIndex      = PacketHeader::BitIndex::Ack;
    ReadU32(value);
    m_bitIndex = oldBitIndex;
}

void TE::Net::Packet::WriteAckBits(U32 value) {
    assert(GetPacketType() == PacketType::Packet);

    I32 oldBitIndex = m_bitIndex;
    m_bitIndex      = PacketHeader::BitIndex::AckBits;
    Reset32Bits();
    m_bitIndex = PacketHeader::BitIndex::AckBits;
    WriteU32(value);
    m_bitIndex = oldBitIndex;
}

void TE::Net::Packet::ReadAckBits(U32 &value) {
    assert(GetPacketType() == PacketType::Packet);

    I32 oldBitIndex = m_bitIndex;
    m_bitIndex      = PacketHeader::BitIndex::AckBits;
    ReadU32(value);
    m_bitIndex = oldBitIndex;
}

void TE::Net::Packet::SetPacketBuffer(U8 *buffer, U32 size) {
    m_bitIndex    = 0;
    m_maxBitIndex = size * 8;

    m_buffer.resize((m_maxBitIndex + 7) / 8);

    memcpy(&m_buffer[0], buffer, (m_maxBitIndex + 7) / 8);
}

Enum TE::Net::Packet::GetPacketType() {
    I32 oldBitIndex = m_bitIndex;
    m_bitIndex      = PacketHeader::BitIndex::PacketType;
    bool isPacket;
    ReadBool(isPacket);
    m_bitIndex = oldBitIndex;

    return isPacket ? PacketType::Packet : PacketType::Message;
}

I32 TE::Net::Packet::GetBitIndex() const { return m_bitIndex; }

void TE::Net::Packet::SetBitIndex(I32 value) {
    if (value < 0 || (value + 7) / 8 > static_cast<I32>(m_buffer.size())) {
        throw std::out_of_range("Unable to set the bit index outside of the buffer size.");
    }

    m_bitIndex = value;
}

I32 TE::Net::Packet::GetMaxBitIndex() const { return m_maxBitIndex; }

void TE::Net::Packet::SetMaxBitIndex(I32 value) {
    if (value < 0 || (value + 7) / 8 > static_cast<I32>(m_buffer.size())) {
        throw std::out_of_range("Unable to set the max bit index outside of the buffer size.");
    }
    m_maxBitIndex = value;
}

U32 TE::Net::Packet::GetHeaderSize() {
    static U32 headerSize =
        (GetPacketType() == PacketType::Packet) ? ::packetHeaderSize : ::messageHeaderSize;

    return headerSize;
}

I32 TE::Net::Packet::GetLength() const { return static_cast<I32>(m_buffer.size()); }

const char *TE::Net::Packet::GetBuffer() const {
    return reinterpret_cast<const char *>(&m_buffer[0]);
}

std::string TE::Net::Packet::Trace() const {
    std::string s = "";
    for (I32 copyBits = 0; copyBits < static_cast<I32>(m_buffer.size() * 8); ++copyBits) {
        s += ((m_buffer[copyBits / 8] >> (7 - copyBits % 8)) & 0x1) == 0 ? "0" : "1";
        if ((copyBits + 1) % 4 == 0 && copyBits != 0) {
            s += " ";
            if ((copyBits + 1) % 8 == 0) {
                s += " ";
            }
        }
    }
    return s;
}

void TE::Net::Packet::RoundUpToByte() { m_bitIndex = (m_bitIndex + 7) / 8 * 8; }

void TE::Net::Packet::ReadLength() {
    I32 oldBitIndex = m_bitIndex;
    m_bitIndex      = PacketHeader::BitIndex::PacketLength;
    m_maxBitIndex   = 0;
    U32 length;
    if (ReadU32(length)) {
        m_maxBitIndex = static_cast<I32>(length);
    }
    m_bitIndex = oldBitIndex;
}

void TE::Net::Packet::BeginPacket(Enum type) {
    m_packetStarted = true;

    m_bitIndex      = 0;
    m_maxBitIndex   = 0;
    m_buffer.clear();

    WriteU32(0);                           // packet length
    WriteBool(type == PacketType::Packet); // packet type

    if (type == PacketType::Packet) {
        WriteU16(0); // protocolID
        WriteU32(0); // sequenceNo
        WriteU32(0); // ack
        WriteU32(0); // ackBits
    } else {
        WriteI8(-1); // message type
    }
}

void TE::Net::Packet::EndPacket() {
    m_packetEnded   = true;

    I32 oldBitIndex = m_bitIndex;
    m_bitIndex      = PacketHeader::BitIndex::PacketLength;
    WriteU32(static_cast<U32>(m_maxBitIndex));
    m_bitIndex = oldBitIndex;
}

void TE::Net::Packet::WriteBool(bool value) {
    ExpandBuffer(1);
    if (value)
        m_buffer[m_bitIndex / 8] |= static_cast<U8>(1 << (7 - m_bitIndex % 8));
    ++m_bitIndex;
}

void TE::Net::Packet::WriteU8(U8 value) {
    ExpandBuffer(8);
    I32 offset = m_bitIndex % 8;
    m_buffer[m_bitIndex / 8] |= value >> offset;
    if (offset != 0) {
        m_buffer[m_bitIndex / 8 + 1] |= value << (8 - offset);
    }
    m_bitIndex += 8;
}

void TE::Net::Packet::WriteI8(I8 value) {
    WriteU8(value);
    /* Shift on signed are undefined behaviour and implementation dependent.. leaving just to be
    sure fix is working.

     ExpandBuffer(8);
        I32 offset = m_bitIndex % 8;
    m_buffer[m_bitIndex / 8] |= value >> offset;
        if (offset != 0)
        {
                m_buffer[m_bitIndex / 8 + 1] |= value << (8 - offset);
        }

    m_bitIndex += 8;*/
}

void TE::Net::Packet::WriteU16(U16 value) {
    ExpandBuffer(16);
    I32 offset = m_bitIndex % 8;
    m_buffer[m_bitIndex / 8] |= value >> (8 + offset);
    m_buffer[m_bitIndex / 8 + 1] |= value >> offset;
    if (offset != 0) {
        m_buffer[m_bitIndex / 8 + 2] |= value << (8 - offset);
    }
    m_bitIndex += 16;
}

void TE::Net::Packet::WriteI16(I16 value) {
    WriteU16(value);
    /* Shift on signed are undefined behaviour and implementation dependent.. leaving just to be
    sure fix is working. ExpandBuffer(16); I32 offset = m_bitIndex % 8; m_buffer[m_bitIndex / 8] |=
    value >> (8 + offset); m_buffer[m_bitIndex / 8 + 1] |= value >> offset; if (offset != 0)
        {
                m_buffer[m_bitIndex / 8 + 2] |= value << (8 - offset);
        }
    m_bitIndex += 16;*/
}

void TE::Net::Packet::WriteU32(U32 value) {
    ExpandBuffer(32);
    I32 offset = m_bitIndex % 8;
    m_buffer[m_bitIndex / 8] |= value >> (24 + offset);
    m_buffer[m_bitIndex / 8 + 1] |= value >> (16 + offset);
    m_buffer[m_bitIndex / 8 + 2] |= value >> (8 + offset);
    m_buffer[m_bitIndex / 8 + 3] |= value >> offset;
    if (offset != 0) {
        m_buffer[m_bitIndex / 8 + 4] |= value << (8 - offset);
    }
    m_bitIndex += 32;
}

bool TE::Net::Packet::ReadU32(U32 &value) {
    value = 0;
    if ((m_bitIndex + 32 + 7) / 8 > static_cast<I32>(m_buffer.size())) {
        return false;
    }
    I32 offset = m_bitIndex % 8;
    value |= m_buffer[m_bitIndex / 8] << (24 + offset);
    value |= m_buffer[m_bitIndex / 8 + 1] << (16 + offset);
    value |= m_buffer[m_bitIndex / 8 + 2] << (8 + offset);
    value |= m_buffer[m_bitIndex / 8 + 3] << offset;
    if (offset != 0) {
        value |= m_buffer[m_bitIndex / 8 + 4] >> (8 - offset);
    }
    m_bitIndex += 32;
    return true;
}

void TE::Net::Packet::WriteI32(I32 value) {
    WriteU32(value);
    /* Shift on signed are undefined behaviour and implementation dependent.. leaving just to be
    sure fix is working. ExpandBuffer(32); I32 offset = m_bitIndex % 8; m_buffer[m_bitIndex / 8] |=
    value >> (24 + offset); m_buffer[m_bitIndex / 8 + 1] |= value >> (16 + offset);
        m_buffer[m_bitIndex / 8 + 2] |= value >> (8 + offset);
        m_buffer[m_bitIndex / 8 + 3] |= value >> offset;
        if (offset != 0)
        {
                m_buffer[m_bitIndex / 8 + 4] |= value << (8 - offset);
        }
    m_bitIndex += 32;*/
}

void TE::Net::Packet::WriteU32(U32 value, I32 bits) {
    if (bits < 1 || bits > 32)
        throw std::out_of_range("bits must be in the range (0, 32].");
    if (bits != 32 && value > static_cast<U32>((0x1 << bits) - 1)) {
        std::ostringstream exceptionStr;
        exceptionStr << "Value does not fit into " << bits << " bits.";
        throw std::out_of_range(exceptionStr.str());
    }

    ExpandBuffer(bits);

    value <<= 32 - bits;

    I32 offset = m_bitIndex % 8;
    m_buffer[m_bitIndex / 8] |= value >> (24 + offset);
    if (offset + bits > 8) {
        m_buffer[m_bitIndex / 8 + 1] |= value >> (16 + offset);
        if (offset + bits > 16) {
            m_buffer[m_bitIndex / 8 + 2] |= value >> (8 + offset);
            if (offset + bits > 24) {
                m_buffer[m_bitIndex / 8 + 3] |= value >> offset;
                if (offset + bits > 32) {
                    m_buffer[m_bitIndex / 8 + 4] |= value << (8 - offset);
                }
            }
        }
    }
    m_bitIndex += bits;
}

void TE::Net::Packet::WriteI32(I32 value, I32 bits) {
    if (bits < 1 || bits > 32)
        throw std::out_of_range("bits must be in the range (0, 32].");
    if (bits != 32 && (value < -(0x1 << (bits - 1)) || value >= 0x1 << (bits - 1))) {
        std::ostringstream exceptionStr;
        exceptionStr << "Value does not fit into " << bits << " bits.";
        throw std::out_of_range(exceptionStr.str());
    }

    ExpandBuffer(bits);

    value <<= 32 - bits;
    U32 uvalue = *reinterpret_cast<U32 *>(&value);

    I32 offset = m_bitIndex % 8;
    m_buffer[m_bitIndex / 8] |= uvalue >> (24 + offset);
    if (offset + bits > 8) {
        m_buffer[m_bitIndex / 8 + 1] |= uvalue >> (16 + offset);
        if (offset + bits > 16) {
            m_buffer[m_bitIndex / 8 + 2] |= uvalue >> (8 + offset);
            if (offset + bits > 24) {
                m_buffer[m_bitIndex / 8 + 3] |= uvalue >> offset;
                if (offset + bits > 32) {
                    m_buffer[m_bitIndex / 8 + 4] |= uvalue << (8 - offset);
                }
            }
        }
    }
    m_bitIndex += bits;
}

void TE::Net::Packet::WriteF32(F32 value) { WriteU32(*reinterpret_cast<U32 *>(&value)); }

void TE::Net::Packet::WriteF64(F64 value) {
    U32 *ints = reinterpret_cast<U32 *>(&value);
    WriteU32(ints[0]);
    WriteU32(ints[1]);
}

void TE::Net::Packet::WriteDynamicU32(U32 value, I32 bits) {
    if (bits < 1 || bits > 32)
        throw std::out_of_range("bits must be in the range (0, 32].");
    I32 shift = bits;
    // Stop when our value can fit inside
    for (; shift < 32 && value >= static_cast<U32>(0x1 << shift); shift += bits) {
        WriteBool(true); // Write a 1 for a continuation bit signifying one more interval is needed
    }
    if (shift < 32) {
        WriteBool(false); // Write a 0 for a continuation bit signifying the end
    }
    WriteU32(value, shift >= 32 ? 32 : shift);
}

void TE::Net::Packet::WriteDynamicU32(U32 value) { WriteDynamicU32(value, 4); }

void TE::Net::Packet::WriteDynamicI32(I32 value, I32 bits) {
    if (bits < 1 || bits > 32)
        throw std::out_of_range("bits must be in the range (0, 32].");
    I32 shift = bits;
    // Stop when our value can fit inside
    for (; shift < 32 && (value < -(0x1 << (shift - 1)) || value >= 0x1 << (shift - 1));
         shift += bits) {
        WriteBool(true); // Write a 1 for a continuation bit signifying one more interval is needed
    }
    if (shift < 32) {
        WriteBool(false); // Write a 0 for a continuation bit signifying the end
    }
    WriteI32(value, shift >= 32 ? 32 : shift);
}

void TE::Net::Packet::WriteDynamicI32(I32 value) { WriteDynamicI32(value, 4); }

void TE::Net::Packet::WriteCustomResolutionF32(F32 value, F32 min, F32 max, I32 bitResolution) {
    if (bitResolution < 1 || bitResolution > 31)
        throw std::out_of_range("bitResolution must be in the range (0, 32).");
    if (min > max)
        throw std::out_of_range("min argument must be less than the max argument.");
    if (value < min || value > max)
        throw std::out_of_range("The value must be on the interval [min, max]");
    U32 uValue;
    if (min < 0 && max > 0) {
        uValue = value == 0 ? 0
                            : static_cast<U32>((value - min) / (max - min) *
                                                   static_cast<F32>((0x1 << bitResolution) - 2) +
                                               0.5) +
                                  1;
    } else {
        uValue = static_cast<U32>(
            (value - min) / (max - min) * static_cast<F32>((0x1 << bitResolution) - 1) + 0.5);
    }
    WriteU32(uValue, bitResolution);
}

void TE::Net::Packet::WriteCustomResolutionF64(F64 value, F64 min, F64 max, I32 bitResolution) {
    if (bitResolution < 1 || bitResolution > 31)
        throw std::out_of_range("bitResolution must be in the range (0, 32).");
    if (min > max)
        throw std::out_of_range("min argument must be less than the max argument.");
    if (value < min || value > max)
        throw std::out_of_range("The value must be on the interval [min, max]");
    U32 uValue;
    if (min < 0 && max > 0) {
        uValue = value == 0 ? 0
                            : static_cast<U32>((value - min) / (max - min) *
                                                   static_cast<F64>((0x1 << bitResolution) - 2) +
                                               0.5) +
                                  1;
    } else {
        uValue = static_cast<U32>(
            (value - min) / (max - min) * static_cast<F64>((0x1 << bitResolution) - 1) + 0.5);
    }
    WriteU32(uValue, bitResolution);
}

void TE::Net::Packet::WriteString(const std::string &value, I32 bits) {
    if (bits < 1 || bits > 31)
        throw std::out_of_range("bits must be in the range (0, 32).");
    U32 size = static_cast<U32>(value.length());
    WriteDynamicU32(size, bits);
    for (std::string::const_iterator strItr = value.begin(); strItr != value.end(); ++strItr) {
        WriteU8(*strItr);
    }
}

void TE::Net::Packet::WriteString(const std::string &value) { WriteString(value, 4); }

void TE::Net::Packet::WriteBinaryPacket(const Packet &value) {
    I32 valueBitIndex    = 0;
    I32 valueMaxBitIndex = value.m_maxBitIndex;
    WriteDynamicU32(static_cast<U32>(valueMaxBitIndex));
    for (I32 copyBytes = 0; copyBytes < valueMaxBitIndex / 8; ++copyBytes) {
        U8 valueByte = 0;
        I32 offset   = valueBitIndex % 8;
        valueByte |= value.m_buffer[valueBitIndex / 8] << offset;
        if (offset != 0) {
            valueByte |= value.m_buffer[valueBitIndex / 8 + 1] >> (8 - offset);
        }
        valueBitIndex += 8;
        WriteU8(valueByte);
    }
    for (I32 copyBits = 0; copyBits < valueMaxBitIndex % 8; ++copyBits) {
        bool valueBit = false;
        if ((valueBitIndex + 1 + 7) / 8 <= static_cast<I32>(value.m_buffer.size())) {
            valueBit = ((value.m_buffer[valueBitIndex / 8] >> (7 - valueBitIndex % 8)) & 0x1) == 1;
        }
        ++valueBitIndex;
        WriteBool(valueBit);
    }
    m_bitIndex += valueMaxBitIndex;
}

// Read Methods

bool TE::Net::Packet::ReadEventID(U32 &value) { return ReadDynamicU32(value, 6); }

bool TE::Net::Packet::ReadBool(bool &value) {
    value = false;
    if ((m_bitIndex + 1 + 7) / 8 > static_cast<I32>(m_buffer.size())) {
        return false;
    }
    value = ((m_buffer[m_bitIndex / 8] >> (7 - m_bitIndex % 8)) & 0x1) == 1;
    ++m_bitIndex;
    return true;
}

bool TE::Net::Packet::ReadU8(U8 &value) {
    value = 0;
    if ((m_bitIndex + 8 + 7) / 8 > static_cast<I32>(m_buffer.size())) {
        return false;
    }
    I32 offset = m_bitIndex % 8;
    value |= m_buffer[m_bitIndex / 8] << offset;
    if (offset != 0) {
        value |= m_buffer[m_bitIndex / 8 + 1] >> (8 - offset);
    }
    m_bitIndex += 8;
    return true;
}

bool TE::Net::Packet::ReadI8(I8 &value) {
    value = 0;
    if ((m_bitIndex + 8 + 7) / 8 > static_cast<I32>(m_buffer.size())) {
        return false;
    }
    I32 offset = m_bitIndex % 8;
    value |= m_buffer[m_bitIndex / 8] << offset;
    if (offset != 0) {
        value |= m_buffer[m_bitIndex / 8 + 1] >> (8 - offset);
    }
    m_bitIndex += 8;
    return true;
}

bool TE::Net::Packet::ReadU16(U16 &value) {
    value = 0;
    if ((m_bitIndex + 16 + 7) / 8 > static_cast<I32>(m_buffer.size())) {
        return false;
    }
    I32 offset = m_bitIndex % 8;
    value |= m_buffer[m_bitIndex / 8] << (8 + offset);
    value |= m_buffer[m_bitIndex / 8 + 1] << offset;
    if (offset != 0) {
        value |= m_buffer[m_bitIndex / 8 + 2] >> (8 - offset);
    }
    m_bitIndex += 16;
    return true;
}

bool TE::Net::Packet::ReadI16(I16 &value) {
    value = 0;
    if ((m_bitIndex + 16 + 7) / 8 > static_cast<I32>(m_buffer.size())) {
        return false;
    }
    I32 offset = m_bitIndex % 8;
    value |= m_buffer[m_bitIndex / 8] << (8 + offset);
    value |= m_buffer[m_bitIndex / 8 + 1] << offset;
    if (offset != 0) {
        value |= m_buffer[m_bitIndex / 8 + 2] >> (8 - offset);
    }
    m_bitIndex += 16;
    return true;
}

bool TE::Net::Packet::ReadI32(I32 &value) {
    value = 0;
    if ((m_bitIndex + 32 + 7) / 8 > static_cast<I32>(m_buffer.size())) {
        return false;
    }
    I32 offset = m_bitIndex % 8;
    value |= m_buffer[m_bitIndex / 8] << (24 + offset);
    value |= m_buffer[m_bitIndex / 8 + 1] << (16 + offset);
    value |= m_buffer[m_bitIndex / 8 + 2] << (8 + offset);
    value |= m_buffer[m_bitIndex / 8 + 3] << offset;
    if (offset != 0) {
        value |= m_buffer[m_bitIndex / 8 + 4] >> (8 - offset);
    }
    m_bitIndex += 32;
    return true;
}

bool TE::Net::Packet::ReadU32(U32 &value, I32 bits) {
    if (bits < 1 || bits > 32)
        throw std::out_of_range("bits must be in the range (0, 32].");

    value = 0;
    if ((m_bitIndex + bits + 7) / 8 > static_cast<I32>(m_buffer.size())) {
        return false;
    }

    I32 offset = m_bitIndex % 8;
    value      = m_buffer[m_bitIndex / 8] << (24 + offset);
    if (offset + bits > 8) {
        value |= m_buffer[m_bitIndex / 8 + 1] << (16 + offset);
        if (offset + bits > 16) {
            value |= m_buffer[m_bitIndex / 8 + 2] << (8 + offset);
            if (offset + bits > 24) {
                value |= m_buffer[m_bitIndex / 8 + 3] << offset;
                if (offset + bits > 32) {
                    value |= m_buffer[m_bitIndex / 8 + 4] >> (8 - offset);
                }
            }
        }
    }

    value >>= 32 - bits;
    m_bitIndex += bits;
    return true;
}

bool TE::Net::Packet::ReadI32(I32 &value, I32 bits) {
    if (bits < 1 || bits > 32)
        throw std::out_of_range("bits must be in the range (0, 32].");

    value = 0;
    if ((m_bitIndex + bits + 7) / 8 > static_cast<I32>(m_buffer.size())) {
        return false;
    }

    I32 offset = m_bitIndex % 8;
    value      = m_buffer[m_bitIndex / 8] << (24 + offset);
    if (offset + bits > 8) {
        value |= m_buffer[m_bitIndex / 8 + 1] << (16 + offset);
        if (offset + bits > 16) {
            value |= m_buffer[m_bitIndex / 8 + 2] << (8 + offset);
            if (offset + bits > 24) {
                value |= m_buffer[m_bitIndex / 8 + 3] << offset;
                if (offset + bits > 32) {
                    value |= m_buffer[m_bitIndex / 8 + 4] >> (8 - offset);
                }
            }
        }
    }

    value >>= 32 - bits;
    m_bitIndex += bits;
    return true;
}

bool TE::Net::Packet::ReadF32(F32 &value) {
    value = 0;
    if ((m_bitIndex + 32 + 7) / 8 > (I32)m_buffer.size()) {
        return false;
    }
    U32 uValue;
    if (!ReadU32(uValue))
        return false;
    value = *reinterpret_cast<F32 *>(&uValue);
    return true;
}

bool TE::Net::Packet::ReadF64(F64 &value) {
    value = 0;
    if ((m_bitIndex + 64 + 7) / 8 > (I32)m_buffer.size()) {
        return false;
    }
    U32 ints[2];
    if (!ReadU32(ints[0]))
        return false;
    if (!ReadU32(ints[1]))
        return false;
    value = *reinterpret_cast<F64 *>(ints);
    return true;
}

bool TE::Net::Packet::ReadDynamicU32(U32 &value, I32 bits) {
    if (bits < 1 || bits > 32)
        throw std::out_of_range("bits must be in the range (0, 32].");
    value                     = 0;
    I32 valueBitCount         = bits;
    bool continuationBitValue = true;
    do {
        if (!ReadBool(continuationBitValue))
            return false;
        if (continuationBitValue)
            valueBitCount += bits;
    } while (continuationBitValue && valueBitCount < 32);
    return ReadU32(value, valueBitCount >= 32 ? 32 : valueBitCount);
}

bool TE::Net::Packet::ReadDynamicU32(U32 &value) { return ReadDynamicU32(value, 4); }

bool TE::Net::Packet::ReadDynamicI32(I32 &value, I32 bits) {
    if (bits < 1 || bits > 32)
        throw std::out_of_range("bits must be in the range (0, 32].");
    value                     = 0;
    I32 valueBitCount         = bits;
    bool continuationBitValue = true;
    do {
        if (!ReadBool(continuationBitValue))
            return false;
        if (continuationBitValue)
            valueBitCount += bits;
    } while (continuationBitValue && valueBitCount < 32);
    return ReadI32(value, valueBitCount >= 32 ? 32 : valueBitCount);
}

bool TE::Net::Packet::ReadDynamicI32(I32 &value) { return ReadDynamicI32(value, 4); }

bool TE::Net::Packet::ReadCustomResolutionF32(F32 &value, F32 min, F32 max, I32 bitResolution) {
    if (bitResolution < 1 || bitResolution > 31)
        throw std::out_of_range("bitResolution must be in the range (0, 32).");
    if (min > max)
        throw std::out_of_range("min argument must be less than the max argument.");
    value = 0;
    U32 uValue;
    if (!ReadU32(uValue, bitResolution))
        return false;
    if (min < 0 && max > 0) {
        value = uValue == 0
                  ? 0
                  : (uValue - 1) / static_cast<F32>((0x1 << bitResolution) - 2) * (max - min) + min;
    } else {
        value = uValue / static_cast<F32>((0x1 << bitResolution) - 1) * (max - min) + min;
    }
    return true;
}

bool TE::Net::Packet::ReadCustomResolutionF64(F64 &value, F64 min, F64 max, I32 bitResolution) {
    if (bitResolution < 1 || bitResolution > 31)
        throw std::out_of_range("bitResolution must be in the range (0, 32).");
    if (min > max)
        throw std::out_of_range("min argument must be less than the max argument.");
    value = 0;
    U32 uValue;
    if (!ReadU32(uValue, bitResolution))
        return false;
    if (min < 0 && max > 0) {
        value = uValue == 0
                  ? 0
                  : (uValue - 1) / static_cast<F64>((0x1 << bitResolution) - 2) * (max - min) + min;
    } else {
        value = uValue / static_cast<F64>((0x1 << bitResolution) - 1) * (max - min) + min;
    }
    return true;
}

bool TE::Net::Packet::ReadString(std::string &value, I32 bits) {
    if (bits < 1 || bits > 31)
        throw std::out_of_range("bits must be in the range (0, 32).");
    value = "";
    U32 size;
    if (!ReadDynamicU32(size, bits))
        return false;
    for (U32 strItr = 0; strItr < size; ++strItr) {
        U8 c;
        if (!ReadU8(c))
            return false;
        value += c;
    }
    return true;
}

bool TE::Net::Packet::ReadString(std::string &value) { return ReadString(value, 4); }

bool TE::Net::Packet::ReadBinaryPacket(TE::Net::Packet &value) {
    U32 valueMaxBitIndex;
    if (!ReadDynamicU32(valueMaxBitIndex))
        return false;
    for (U32 copyBytes = 0; copyBytes < valueMaxBitIndex / 8; ++copyBytes) {
        U8 valueByte;
        if (!ReadU8(valueByte))
            return false;
        value.WriteU8(valueByte);
    }
    for (U32 copyBits = 0; copyBits < valueMaxBitIndex % 8; ++copyBits) {
        bool valueBit;
        if (!ReadBool(valueBit))
            return false;
        value.WriteBool(valueBit);
    }
    m_bitIndex += static_cast<I32>(valueMaxBitIndex);
    value.m_bitIndex = 0;
    return true;
}

void TE::Net::Packet::ExpandBuffer(I32 bits) {
    if (bits < 1)
        throw std::out_of_range("bits must be greater than 0");

    while ((m_bitIndex + bits + 7) / 8 > static_cast<I32>(m_buffer.size())) {
        m_buffer.push_back(0);
    }

    m_maxBitIndex = std::max<I32>(m_maxBitIndex, m_bitIndex + bits);
}

void TE::Net::Packet::StartReading() {
    U32 readIndex =
        (GetPacketType() == PacketType::Packet) ? ::packetReadIndex : ::messageReadIndex;

    SetBitIndex(readIndex);
}

bool TE::Net::Packet::IsStartedAndEnded() { return m_packetStarted && m_packetEnded; }

void TE::Net::Packet::Reset32Bits() {
    ExpandBuffer(32);
    I32 offset = m_bitIndex % 8;
    m_buffer[m_bitIndex / 8] &= 0xFF << (8 - offset);
    m_buffer[m_bitIndex / 8 + 1] = 0;
    m_buffer[m_bitIndex / 8 + 2] = 0;
    m_buffer[m_bitIndex / 8 + 3] = 0;
    if (offset != 0) {
        m_buffer[m_bitIndex / 8 + 4] &= 0xFF >> offset;
    }
    m_bitIndex += 32;
}

void TE::Net::Packet::Reset8Bits() {
    ExpandBuffer(8);
    I32 offset = m_bitIndex % 8;
    m_buffer[m_bitIndex / 8] &= 0xFF << (8 - offset);
    if (offset != 0) {
        m_buffer[m_bitIndex / 8 + 1] &= 0xFF >> offset;
    }
    m_bitIndex += 8;
}

TE::Math::Vector3D<F32> TE::Net::ReadVector(TE::Net::Packet &packet) {
    TE::Math::Vector3D<F32> vec;

    packet.ReadF32(vec.x);
    packet.ReadF32(vec.y);
    packet.ReadF32(vec.z);

    return vec;
}

void TE::Net::WriteVector(const TE::Math::Vector3D<F32> &vec, TE::Net::Packet &packet) {
    packet.WriteF32(vec.x);
    packet.WriteF32(vec.y);
    packet.WriteF32(vec.z);
}

TE::Math::Quaternion<F32> TE::Net::ReadQuaternion(TE::Net::Packet &packet) {
    TE::Math::Quaternion<F32> quat;

    packet.ReadF32(quat.x);
    packet.ReadF32(quat.y);
    packet.ReadF32(quat.z);
    packet.ReadF32(quat.w);

    return quat;
}

void TE::Net::WriteQuaternion(const TE::Math::Quaternion<F32> &quat, TE::Net::Packet &packet) {
    packet.WriteF32(quat.x);
    packet.WriteF32(quat.y);
    packet.WriteF32(quat.z);
    packet.WriteF32(quat.w);
}
