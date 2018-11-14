#ifndef TENEW_H
#define TENEW_H

#include <string>
#include <unordered_map>
#include <iostream>
#include <assert.h>
#include "TEDataTypes.h"

namespace TE
{
	namespace Memory
	{
		class NewReplacement
		{
			struct NewInfo
			{
				U32 id;
				std::string filename;
				U32 line;
				size_t bytes;
				U32 dimensions;
			};
			typedef std::unordered_map<void*, NewInfo> NewInfoMap;
		public:
			NewReplacement(const std::string& filename, I32 line, U32 allocator = -1)
				:
				m_filename(filename),
				m_line(line),
				m_allocator(allocator)
			{}
			~NewReplacement(){}
			
			static void Cleanup();

			static void PrintMemoryLogToClog();
			static void PrintMemoryLog();
			static void PrintMemoryLogToFile(const std::string& filename);
			
			void* Allocate(size_t bytes, U32 dimensions) const;

			void Deallocate(void* memory);

			template <typename T>
			T* New1(const U32 size0)
			{
				T* memory;

				memory = static_cast<T*>(Allocate(size0 * sizeof(T), 1));

				T* object = memory;
				for (U32 i = 0; i < size0; ++i, ++object)
				{
					::new(object) T;
				}

				return memory;
			}

			template <typename T>
			T** New2(const U32 size0, const U32 size1)
			{
				throw "Not Implemented";
			}

			template <typename T>
			T*** New3(const U32 size0, const U32 size1, const U32 size2)
			{
				throw "Not Implemented";
			}

			template <typename T>
			T**** New4(const U32 size0, const U32 size1, const U32 size2, const U32 size3)
			{
				throw "Not Implemented";
			}

			template <typename T>
			void Delete0(T*& memory)
			{
				if (!memory) return;
				
				NewInfoMap::iterator findItr = GetNewInfoMap().find(memory);
				assert(findItr != GetNewInfoMap().end() && "Memory not in memory map");
				assert(findItr->second.dimensions == 0 && "Memory missmatch");
				
				memory->~T();

				Deallocate(memory);

				memory = NULL;
			}

			template <typename T>
			void Delete1(T*& memory)
			{
				if (memory)
				{
					NewInfoMap::iterator findItr = GetNewInfoMap().find(memory);

					assert(findItr->second.dimensions == 1 && "Dimension mismatch");

					// Call destructor for T.  If T is a pointer type, the
					// compiler will not generate any code for the destructor
					// call.
					const U32 numElements = findItr->second.bytes/sizeof(T);
					T* object = memory;
					for (U32 i = 0; i < numElements; ++i, ++object)
					{
						object->~T();
					}

					// Remove T[] from memory map.
					Deallocate(memory);
				}
			}

			template <typename T>
			void Delete2(T**& memory)
			{
				throw "Not Implemented";
			}

			template <typename T>
			void Delete3(T***& memory)
			{
				throw "Not Implemented";
			}

			template <typename T>
			void Delete4(T****& memory)
			{
				throw "Not Implemented";
			}
		private:
			std::string m_filename;
			U32 m_line;
			I32 m_allocator;
			
			static std::string GetMemoryLogString();
			static NewInfoMap& GetNewInfoMap();
		};
	}
}

inline void* operator new (size_t numBytes, const TE::Memory::NewReplacement& newReplacement)
{
	return newReplacement.Allocate(numBytes, 0);
}

inline void operator delete (void*, const TE::Memory::NewReplacement& newReplacement)
{
	//Exceptions only
}

#define new0 new(TE::Memory::NewReplacement(__FILE__,__LINE__))
#define new1 TE::Memory::NewReplacement(__FILE__,__LINE__).New1
#define new2 TE::Memory::NewReplacement(__FILE__,__LINE__).New2
#define new3 TE::Memory::NewReplacement(__FILE__,__LINE__).New3
#define new4 TE::Memory::NewReplacement(__FILE__,__LINE__).New4

#define delete0 TE::Memory::NewReplacement(__FILE__,__LINE__).Delete0
#define delete1 TE::Memory::NewReplacement(__FILE__,__LINE__).Delete1
#define delete2 TE::Memory::NewReplacement(__FILE__,__LINE__).Delete2
#define delete3 TE::Memory::NewReplacement(__FILE__,__LINE__).Delete3
#define delete4 TE::Memory::NewReplacement(__FILE__,__LINE__).Delete4

#endif