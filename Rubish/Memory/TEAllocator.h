#ifndef TEALLOCATOR_H
#define TEALLOCATOR_H

#include <unordered_map>
#include "TESmartPointers.h"

namespace TE
{

	namespace Memory
	{
		class Allocator
		{
		public:
			Allocator(){}
			virtual ~Allocator(){}

			virtual void* Allocate(unsigned bytes)  const = 0;
			virtual void  Deallocate(void *memory) const = 0;
			virtual void  Clear() = 0;
		};
	}
}

#endif