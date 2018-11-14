/**
 *	\file		TEPacking.h
 *  \author		Terje Loe
 *  \brief		Defenitions for Packng class
 *				Binary packer based on article and code from http://gpwiki.org/index.php/Binary_Packet
 */

#ifndef TEPACKING_H
#define TEPACKING_H

#include <vector>
#include <sstream>
#include <stdexcept>
#include "TEDataTypes.h"

namespace TE
{
	namespace Network
	{
		// Binary Writer/Reader
		// bool             - 1 byte
		// [unsigned] char  - 1 byte
		// [unsigned] short - 2 bytes
		// [unsigned] I32   - 4 bytes
		// F32            - 4 bytes
		// F64           - 8 bytes
		// String - No unicode support. C++ has none. Choose a library and implement it if you need it.
		class Packet
		{
		private:
			std::vector<U8> buffer;
			I32 bitIndex;
			I32 maxBitIndex;

			// Expands the buffer size appending bytes so that the write functions don't overflow.
			// Records the furthest write in the maxBitIndex
			// bits: The number of bits to allocate and record.
			void ExpandBuffer(I32 bits);

		public:
			// Constructor.
			Packet();

			// Fills the buffer with the requested bytes to work with.
			// buffer: The bytes to load into the buffer.
			Packet(U8* buffer, I32 maxBitIndex);

			// Gets the bit index.
			I32 GetBitIndex() const;

			// Sets the bit index.
			void SetBitIndex(I32 value);

			// Gets the max bit index.
			I32 GetMaxBitIndex() const;

			// Sets the max bit index.
			// value: the value to set the max bit index to.
			void SetMaxBitIndex(I32 value);

			// Gets the header size for the length in bytes.
			I32 GetHeaderSize() const;

			// Gets the header size for the length in bits.
			I32 GetHeaderSizeInBits() const;

			// Returns the buffer length in bytes.
			I32 GetLength() const;

			// Returns the buffer as an array of bytes.
			const char* GetBuffer();

			// Returns a string of 0s and 1s representing the bits in the buffer. Good for debugging.
			// Places a space between nibbles and two spaces between bytes.
			std::string Trace() const;

			// Rounds the bitIndex up to a byte.
			void RoundUpToByte();

			// Reads the length stored in the header. 
			// BeginPacket and EndPacket should have been called to make this.
			// Note: It's expected 4 bytes are in the buffer before this is called.
			void ReadLength();

			// WRITE METHODS

			// Writes a begin packet header of 32 bits.
			void BeginPacket();

			// Writes maxBitIndex to the packet header created with BeginPacket.
			void EndPacket();

			// Writes an Event ID.
			// value: The event ID normally stored in an enumeration.
			void WriteEventID(U32 value);

			// Writes a single bit either 0 or 1 into the buffer.
			// value: The boolean value to write.
			void WriteBool(bool value);

			// Writes an 8 bit unsigned byte into the buffer.
			// value: The unsigned byte value to write.
			void WriteByte(U8 value);

			// Writes an 8 bit signed byte into the buffer.
			// value: The signed byte value to write.
			void WriteSByte(I8 value);

			// Writes a 16 bit unsigned short into the buffer.
			// value: The unsigned short value to write.
			void WriteUint16(U16 value);

			// Writes a 16 bit signed short into the buffer.
			// value: The signed short value to write.
			void Writeint16(I16 value);

			// Writes a 32 bit unsigned integer into the buffer.
			// value: The unsigned integer value to write.
			void WriteUint32(U32 value);

			// Writes a 32 bit signed integer into the buffer.
			// value: The signed integer value to write.
			void Writeint32(I32 value);

			// Writes an n bit unsigned integer into the buffer.
			// value: The unsigned integer value to write.
			// bits: The number of bits to use.
			void WriteUint(U32 value, I32 bits);

			// Writes an n bit signed integer into the buffer.
			// value: The signed integer value to write.
			// bits: The number of bits to use.
			void Writeint(I32 value, I32 bits);

			// Writes a 32 bit single into the buffer.
			// value: The single value to write.
			void WriteF32(F32 value);

			// Writes a 64 bit F64 into the buffer. 
			// value: The F64 value to write.
			void WriteDouble(F64 value);

			// Writes an integer using a variable width encoding of bits. Choose a bits value that represents the number of bits to hold the average value.
			// value: The unsigned integer value to write.
			// bits: The number of bits to use for the sequence.
			void WriteDynamicUint(U32 value, I32 bits);

			// Default 4 bits.
			// value: The unsigned integer value to write.
			void WriteDynamicUint(U32 value);

			// Writes an integer using a variable length of bits. Choose a bits value that represents the number of bits to hold the average value.
			// value: The signed integer value to write.
			// bits: The number of bits to use for the sequence.
			void WriteDynamicint(I32 value, I32 bits);

			// Default 4 bits.
			// value: The signed integer value to write.
			void WriteDynamicint(I32 value);

			// Creates a value for the ratio: value / (2 ^ bitResolution - 1) in relationship to value / (max - min).
			// This allows F32ing point to have a resolution.
			// value: The F32ing point value in the range.
			// min: The minimum value in the range.
			// max: The maximum value in the range.
			// bitResolution: The number of bits to use for the ratio.
			void WriteCustomResolutionF32(F32 value, F32 min, F32 max, I32 bitResolution);

			// Creates a value for the ratio: value / (2 ^ bitResolution - 1) in relationship to value / (max - min).
			// This allows a F32ing point to have a resolution.
			// value">The F64 value in the range.
			// min">The minimum value in the range.
			// max">The maximum value in the range.
			// bitResolution">The number of bits to use for the ratio.
			void WriteCustomResolutionDouble(F64 value, F64 min, F64 max, I32 bitResolution);

			// Writes the length of the string using WriteDynamicUnsignedinteger and then writes a boolean, true for unicode, false for ascii. 
			// ASCII uses a compression step using either 6 or 7 bits per character.
			// value: The string value to write.
			// bits: The number of bits for the length written using an unsigned dynamic integer.
			void WriteString(const std::string& value, I32 bits);

			// Defaults to 4 arrayBits. Read the overloaded function for a description.
			// value: The string value to Write.
			void WriteString(const std::string& value);

			// Appends a binary packet to the buffer.
			// value: The binary packet to write.
			void WriteBinaryPacket(const Packet& value);

			// READ METHODS

			// Reads an Event ID.
			// value: The event ID normally stored in an enumeration.
			// returns: false on error.
			bool ReadEventID(U32& value);

			// Reads one bit from the buffer.
			// value: Boolean.
			// returns: false on error.
			bool ReadBool(bool& value);

			// Reads an 8 bits unsigned byte from the buffer.
			// value: Unsigned Byte.
			// returns: false on error.
			bool ReadByte(U8& value);

			// Reads an 8 bits signed byte from the buffer.
			// value: Signed Byte.
			// returns: false on error.
			bool ReadSByte(I8& value);

			// Reads a 16 bit unsigned short from the buffer.
			// value: Unsigned Short.
			// returns: false on error.
			bool ReadUint16(U16& value);

			// Reads a 16 bit signed short from the buffer.
			// value: Signed Short.
			// returns: false on error.
			bool Readint16(I16& value);

			// Reads a 32 bit unsigned integer from the buffer.
			// value: Unsigned integer.
			// returns: false on error.
			bool ReadUint32(U32& value);

			// Reads a 32 bit signed integer from the buffer.
			// value: Signed integer.
			// returns: false on error.
			bool Readint32(I32& value);

			// Reads an n bit custom unsigned integer from the buffer.
			// value: Unsigned integer.
			// bits: The number of bits used to write.
			// returns: false on error.
			bool ReadUint(U32& value, I32 bits);

			// Reads an n bit custom signed integer from the buffer.
			// value: Signed integer.
			// bits: The number of bits used to write.
			// returns: false on error.
			bool Readint(I32& value, I32 bits);

			// Reads a 32 bit single from the buffer.
			// value: Single.
			// returns: false on error.
			bool ReadSingle(F32& value);

			// Reads a 64 bit F64 from the buffer.
			// value: Double.
			// returns: false on error.
			bool ReadDouble(F64& value);

			// Reads the dynamic unsigned integer.
			// value: Unsigned integer.
			// bits: The bit size of the sequence used to write.
			// returns: false on error.
			bool ReadDynamicUint(U32& value, I32 bits);

			// Default 4 bits.
			// value: Unsigned integer.
			// returns: false on error.
			bool ReadDynamicUint(U32& value);

			// Reads the dynamic unsigned integer.
			// value: Unsigned integer.
			// bits: The bit size of the sequence used to write.
			// returns: false on error.
			bool ReadDynamicint(I32& value, I32 bits);

			// Default 4 bits.
			// value: Signed integer.
			// returns: false on error.
			bool ReadDynamicint(I32& value);

			// Reads a custom resolution single.
			// value: Single. 
			// min: The minimum value in the range.
			// max: The maximum value in the range.
			// bitResolution: The number of bits written for the ratio.
			// returns: false on error.
			bool ReadCustomResolutionSingle(F32& value, F32 min, F32 max, I32 bitResolution);

			// Reads a custom resolution F64
			// value: Double.
			// min: The minimum value in the range.
			// max: The maximum value in the range.
			// bitResolution: The number of bits written for the ratio.
			// returns: false on error.
			bool ReadCustomResolutionDouble(F64& value, F64 min, F64 max, I32 bitResolution);

			// Reads a string
			// value: String.
			// bits: The number of bits for the length written using an unsigned dynamic integer.
			// returns: false on error.
			bool ReadString(std::string& value, I32 bits);

			// Default 4 bits.
			// value: String.
			// returns: false on error.
			bool ReadString(std::string& value);

			// Reads a binary packet that has been written to the buffer.
			// value: A binary packet.
			// returns: false on error.
			bool ReadBinaryPacket(Packet& value);
		};

		class Packable
		{
			virtual void Pack(Packet &packet) = 0;
			virtual void Unpack(Packet &packet) = 0;
		};

		class PacketQue : public Packable
		{
		public:
			void Add(const Packet& packet)
			{
				m_packets.push_back(packet);
			}

			void Pack(Packet &packet)
			{
				packet.BeginPacket();

				unsigned numPackets = m_packets.size();
				packet.WriteDynamicUint(numPackets);
				for (unsigned i = 0; i < numPackets; ++i)
				{
					packet.WriteBinaryPacket(m_packets[i]);
				}
				
				packet.EndPacket();
			}

			void Unpack(Packet &packet)
			{
				unsigned numPackets;
				packet.ReadDynamicUint(numPackets);
				for (unsigned i = 0; i < numPackets; ++i)
				{
					Packet tmpPacket;
					m_packets.push_back(tmpPacket);
					packet.ReadBinaryPacket(*m_packets.end());
				}
			}

			void Clear()
			{
				m_packets.clear();
			}

			std::vector<Packet>& GetPackets()
			{
				return m_packets;
			}
		private:
			std::vector<Packet> m_packets;
		};
	}
}
#endif