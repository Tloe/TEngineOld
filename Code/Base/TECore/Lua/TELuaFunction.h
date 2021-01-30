#ifndef TELUAFUNCTION_H
#define TELUAFUNCTION_H

#include "TELuaBaseFunction.h"

#include <functional>

#include <lua.hpp>

namespace TE
{
    namespace Lua { class State; }

  namespace Lua
  {
        /*namespace Detail 
        {
            void SetupFunction(State & state, std::string & name);
            void RemoveFunction(State & state, std::string & name);
        }*/

    template <int N, typename Ret, typename... Args>
    class Function : public BaseFunction
    {
      using FunctionType = std::function<Ret(Args...)>;
    public:
      Function(State & state, const std::string &name, Ret(*function)(Args...));

      Function(State & state, const std::string &name, FunctionType function);

      Function(const Function & other) = delete;

      ~Function();

      virtual I32 Execute();

    private:
      FunctionType m_function;
      std::string m_name;
      State & m_state;
    };

        template <int N, typename Ret, typename... Args>
        Function<N, Ret, Args...>::Function(State & state,
                                            const std::string & name,
                                            Ret(*function)(Args...))
      : Function(state, name, FunctionType{ function })
        {
        }

        template <int N, typename Ret, typename... Args>
        Function<N, Ret, Args...>::Function(State & state,
                                            const std::string & name,
                                            FunctionType function)
            : m_function(function), m_name(name), m_state(state)
        {
            lua_pushlightuserdata(StateToNative(m_state), static_cast<void *>(static_cast<BaseFunction *>(this)));
            lua_pushcclosure(StateToNative(state), &LuaDispatcher, 1);
            lua_setglobal(StateToNative(state), m_name.c_str());
        }

        template <int N, typename Ret, typename... Args>
        Function<N, Ret, Args...>::~Function()
        {
            lua_pushnil(StateToNative(m_state));
            lua_setglobal(StateToNative(m_state), m_name.c_str());
        }

        template <int N, typename Ret, typename... Args>
        I32 Function<N, Ret, Args...>::Execute()
        {
            std::tuple<Args...> args = GetArgs<Args...>(m_state);
            Push(m_state, Lift(m_function, args));
            return N;
        }
  }
}

#endif
