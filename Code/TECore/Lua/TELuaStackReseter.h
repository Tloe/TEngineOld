#ifndef TELUASTACKRESETER_H
#define TELUASTACKRESETER_H

#include "TEDataTypes.h"

namespace TE
{
	namespace Lua { class State; }

	namespace Lua
	{
		class StackReseter
		{
		public:
			StackReseter(StackReseter &) = delete;
			StackReseter(StackReseter &&) = delete;
			StackReseter & operator=(StackReseter const &) = delete;
			StackReseter & operator=(StackReseter &&) = delete;

			explicit StackReseter(State & state);
			~StackReseter();
		private:
			State & m_state;
			I32 m_savedStackTop;
		};
	}
}

#endif