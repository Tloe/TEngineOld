#include "TELuaHelpers.h"
#include "TELuaState.h"

#include "lua.hpp"

I32 TE::Lua::LuaAbsoluteIndex(State &state, I32 index) {
    return (index > 0 || index <= LUA_REGISTRYINDEX) ? index : lua_gettop(state()) + index + 1;
}

void TE::Lua::LuaSwap(State &state, I32 index0, I32 index1) {
    index0 = LuaAbsoluteIndex(state, index0);
    index1 = LuaAbsoluteIndex(state, index1);
    lua_pushvalue(state(), index0);
    lua_pushvalue(state(), index1);
    lua_replace(state(), index0);
    lua_replace(state(), index1);
}

void TE::Lua::LuaSwap(State &state) {
    lua_pushvalue(state(), -2);
    lua_remove(state(), -3);
}

void TE::Lua::CreateTableInRegistry(State &state, const std::string &name) {
    lua_pushlstring(state(), name.c_str(), name.size());
    lua_newtable(state());
    lua_settable(state(), LUA_REGISTRYINDEX);
}

lua_State *TE::Lua::StateToNative(State &state) { return state(); }
