#include "TELuaStackReseter.h"
#include "TELuaState.h"

#include "lua.hpp"

TE::Lua::StackReseter::StackReseter(State &state)
    : m_state(state),
      m_savedStackTop(lua_gettop(state())) {
}

TE::Lua::StackReseter::~StackReseter() {
    lua_settop(m_state(), m_savedStackTop);
}
