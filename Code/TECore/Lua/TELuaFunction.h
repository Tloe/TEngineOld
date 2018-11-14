#ifndef TELUAFUNCTION_H
#define TELUAFUNCTION_H

#include "TELuaBaseFunction.h"
#include "TELuaState.h"

#include <functional>

namespace TE
{
	namespace Lua
	{
		template <int N, typename Ret, typename... Args>
		class Function : public BaseFunction
		{
			using FunctionType = std::function<Ret(Args...)>;
		public:
			Function(State & state, const std::string &name, Ret(*function)(Args...))
				: Function(state, name, FunctionType{ function })
			{}

			Function(State & state, const std::string &name, FunctionType function)
				: m_function(function), m_name(name), state(state)
			{
				lua_pushlightuserdata(state(), static_cast<void *>(static_cast<BaseFunction *>(this)));
				lua_pushcclosure(state(), &LuaDispatcher, 1);
				lua_setglobal(state(), m_name.c_str());
			}

			Function(const Function & other) = delete;

			~Function()
			{
				lua_pushnil(state());
				lua_setglobal(state(), m_name.c_str());
			}

			virtual I32 Execute()
			{
				std::tuple<Args...> args = GetArgs<Args...>(state);
				Push(state, Lift(m_function, args));
				return N;
			}

		private:
			FunctionType m_function;
			std::string m_name;
			State & state;
		};
	}
}

#endif
