#ifndef TELUADESTRUCTOR_H
#define TELUADESTRUCTOR_H

#include "TELuaBaseFunction.h"

namespace TE
{
	namespace Lua
	{
		template <typename ClassT>
		class Destructor : public BaseFunction
		{
		public:
			Destructor(State & state, const std::string & metatableName);

			virtual I32 Execute();
		};


		template <typename ClassT>
		TE::Lua::Destructor<ClassT>::Destructor(State & state, const std::string & metatableName)
		{

		}

		template <typename ClassT>
		I32 TE::Lua::Destructor<ClassT>::Execute()
		{
			return 42;
		}
	}
}

#endif
