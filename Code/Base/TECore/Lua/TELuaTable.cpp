#include "TELuaTable.h"

#include "TEFileIO.h"
#include "TELuaState.h"
#include "lua.hpp"

TE::Lua::Table::Table(I32 luaReference, State &luaState)
    : m_state(luaState),
      m_luaReference(luaReference) {
}

TE::Lua::Table::~Table() {
    luaL_unref(m_state(), LUA_REGISTRYINDEX, m_luaReference);
}

TE::Lua::Variable TE::Lua::Table::operator[](const std::string &key) {
    return Variable{m_state, RefFromT(m_state, key)};
}

TE::Lua::Variable TE::Lua::Table::operator[](I32 key) {
    return Variable{m_state, RefFromT(m_state, key)};
}

void TE::Lua::Table::PushToStack() {
    lua_rawgeti(m_state(), LUA_REGISTRYINDEX, m_luaReference);
}

TE::Lua::Table TE::Lua::FromFile(IO::FileIO &fileIO, std::string &filename, State &luaState) {
    luaState.RunFile(fileIO, filename);
    return FromStack(luaState);
}

TE::Lua::Table TE::Lua::FromStack(State &luaState, I32 index) {
    lua_pushvalue(luaState(), index);
    I32 reference = luaL_ref(luaState(), LUA_REGISTRYINDEX);
    return Table(reference, luaState);
}
