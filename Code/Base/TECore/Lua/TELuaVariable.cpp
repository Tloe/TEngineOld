#include "TELuaVariable.h"

#include "TELuaHelpers.h"
#include "TELuaNative.h"
#include "TELuaRef.h"
#include "TELuaState.h"
#include "TELuaTable.h"

#include "lua.hpp"

namespace {
    int ErrorHandler(lua_State *nativeState) {
        const char *message = "No message set";
        if (!lua_isnil(nativeState, -1))
            message = lua_tostring(nativeState, -1);

        lua_pushstring(nativeState, message);

        // call debug.traceback
        lua_getglobal(nativeState, "debug");
        lua_getfield(nativeState, -1, "traceback");
        lua_pushvalue(nativeState, -3);
        lua_pushinteger(nativeState, 2);
        lua_call(nativeState, 2, 1);

        return 1;
    }

    I32 SetErrorHandler(TE::Lua::State &state) {
        lua_pushcfunction(state(), ErrorHandler);
        return lua_gettop(state());
    }
}

TE::Lua::Variable::Variable(State &state, LuaRef keyRef, const std::vector<LuaRef> &keyPath)
    : m_state(state),
      m_keyPath(keyPath),
      m_keyRef(keyRef),
      m_callTriggered(false) {
}

TE::Lua::Variable TE::Lua::Variable::operator[](const std::string &key) const {
    CheckCreateTable();
    auto keyPath = m_keyPath;
    keyPath.emplace_back(m_keyRef);
    return Variable{m_state, RefFromT(m_state, key), keyPath};
}

TE::Lua::Variable TE::Lua::Variable::operator[](const char *key) const {
    return (*this)[std::string{key}];
}

TE::Lua::Variable TE::Lua::Variable::operator[](const I32 key) const {
    CheckCreateTable();
    auto keyPath = m_keyPath;
    keyPath.emplace_back(m_keyRef);
    return Variable{m_state, RefFromT(m_state, key), keyPath};
}

TE::Lua::Variable::operator bool() const {
    StackReseter stackReseter(m_state);
    Get();
    // std::cout << m_state.StackOutputString() << std::endl;
    if (m_callTriggered)
        Call(1);
    // std::cout << m_state.StackOutputString() << std::endl;
    return ReadStack<bool>(Id<bool>{}, m_state);
}

TE::Lua::Variable::operator I32() const {
    StackReseter stackReseter(m_state);
    Get();
    if (m_callTriggered)
        Call(1);
    return ReadStack<I32>(Id<I32>{}, m_state);
}

TE::Lua::Variable::operator U32() const {
    StackReseter stackReseter(m_state);
    Get();
    if (m_callTriggered)
        Call(1);
    return ReadStack<U32>(Id<U32>{}, m_state);
}

TE::Lua::Variable::operator F32() const {
    StackReseter stackReseter(m_state);
    Get();
    if (m_callTriggered)
        Call(1);
    return ReadStack<F32>(Id<F32>{}, m_state);
}

TE::Lua::Variable::operator std::string() const {
    StackReseter stackReseter(m_state);
    Get();
    if (m_callTriggered)
        Call(1);
    return ReadStack<std::string>(Id<std::string>{}, m_state);
}

void TE::Lua::Variable::operator=(bool value) const {
    Store(value);
}

void TE::Lua::Variable::operator=(I32 value) const {
    Store(value);
}

void TE::Lua::Variable::operator=(U32 value) const {
    Store(value);
}

void TE::Lua::Variable::operator=(F32 value) const {
    Store(value);
}

void TE::Lua::Variable::operator=(const std::string &value) const {
    Store(value);
}

void TE::Lua::Variable::operator=(const char *value) const {
    Store(value);
}

void TE::Lua::Variable::Call(I32 returnCount) const {
    m_callTriggered = false;

    ::SetErrorHandler(m_state);
    LuaSwap(m_state);
    const I32 handlerIndex = lua_gettop(m_state()) - 1;

    for (const auto &arg : m_callArgs)
        arg.Push();

    lua_pcall(m_state(), m_callArgs.size(), returnCount, handlerIndex);
}

void TE::Lua::Variable::Get() const {
    TraverseRefs(m_state, m_keyPath);
    m_keyRef.Get();
}

void TE::Lua::Variable::CheckCreateTable() const {
    StackReseter stackReseter(m_state);
    Get();
    if (!lua_istable(m_state(), -1)) {
        lua_pop(m_state(), 1);
        TraverseRefs(m_state, m_keyPath);
        m_keyRef.Push();
        lua_newtable(m_state());
        lua_settable(m_state(), -3);
    }
}

std::string TE::Lua::Variable::FieldName() const {
    std::string fieldName;
    return "42";
}
