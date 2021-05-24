#ifndef TELUABASEFUNCTION_H
#define TELUABASEFUNCTION_H

#include "TELuaNative.h"

#include <lua.hpp>

#include <functional>

namespace TE::Lua {
  class State;

  template <typename Ret> struct RetCount { static constexpr int Count = 1; };

  template <typename... Ret> struct RetCount<std::tuple<Ret...>> {
    static constexpr int Count = sizeof...(Ret);
  };

  template <> struct RetCount<void> { static constexpr int Count = 0; };

  class BaseFunction {
  public:
    virtual ~BaseFunction() {}
    virtual I32 Execute() = 0;
  };

  static int inline LuaDispatcher(lua_State *luaState) {
    TE::Lua::BaseFunction *function =
        static_cast<TE::Lua::BaseFunction *>(lua_touserdata(luaState, lua_upvalueindex(1)));
    return function->Execute();
  }

  template <typename T> T CheckGet(TE::Lua::State &state, int index) {
    // Todo: Check
    return ReadStack<T>(Id<T>{}, state, index);
  }

  template <typename... T, std::size_t... N>
  std::tuple<T...> GetArgs(TE::Lua::State &luaState, Indices<N...>) {
    return std::tuple<T...>{CheckGet<T>(luaState, N + 1)...};
  }

  template <typename... Args> std::tuple<Args...> GetArgs(TE::Lua::State &luaState) {
    constexpr std::size_t argsCount = sizeof...(Args);
    return GetArgs<Args...>(luaState, typename IndicesBuilder<argsCount>::Type());
  }

  template <typename Ret, typename... Args, std::size_t... N>
  Ret Lift(std::function<Ret(Args...)> fun, std::tuple<Args...> arguments, Indices<N...>) {
    return fun(std::get<N>(arguments)...);
  }

  template <typename Ret, typename... Args>
  Ret Lift(std::function<Ret(Args...)> fun, std::tuple<Args...> arguments) {
    return Lift(fun, arguments, typename IndicesBuilder<sizeof...(Args)>::Type());
  }
}

#endif
