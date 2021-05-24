#include "TELuaNative.h"

#include "TELuaState.h"

#include <cassert>
#include <string>
#include <tuple>

#include <lua.hpp>

void TE::Lua::Push(State &state) {}

void TE::Lua::Push(State &state, bool value) { lua_pushboolean(state(), value); }

void TE::Lua::Push(State &state, I32 value) { lua_pushinteger(state(), value); }

void TE::Lua::Push(State &state, U32 value) { lua_pushinteger(state(), value); }

void TE::Lua::Push(State &state, F32 value) { lua_pushnumber(state(), static_cast<double>(value)); }

void TE::Lua::Push(State &state, F64 value) { lua_pushnumber(state(), value); }

void TE::Lua::Push(State &state, const std::string &value) {
    lua_pushstring(state(), value.c_str());
}

void TE::Lua::Push(State &state, const char *value) { lua_pushstring(state(), value); }

bool TE::Lua::Detail::ReadStack(Id<bool> t, State &state, I32 index) {
    assert(lua_isboolean(state(), index));
    return lua_toboolean(state(), index) != 0;
}

I32 TE::Lua::Detail::ReadStack(Id<I32>, State &state, I32 index) {
    assert(lua_isnumber(state(), index));
    return static_cast<I32>(lua_tointeger(state(), index));
}

U32 TE::Lua::Detail::ReadStack(Id<U32>, State &state, I32 index) {
    assert(lua_isnumber(state(), index));
    return static_cast<U32>(lua_tointeger(state(), index));
}

F32 TE::Lua::Detail::ReadStack(Id<F32>, State &state, I32 index) {
    assert(lua_isnumber(state(), index));
    return static_cast<F32>(lua_tonumber(state(), index));
}

F64 TE::Lua::Detail::ReadStack(Id<F64>, State &state, I32 index) {
    assert(lua_isnumber(state(), index));
    return lua_tonumber(state(), index);
}

std::string TE::Lua::Detail::ReadStack(Id<std::string>, State &state, I32 index) {
    assert(lua_isstring(state(), index));
    return std::string{lua_tostring(state(), index)};
}
