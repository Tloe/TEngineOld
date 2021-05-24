#include "TELuaRef.h"

#include <TELuaState.h>

#include "lua.hpp"

namespace {

    class ReFDeleter {
      public:
        ReFDeleter(TE::Lua::State &state) : m_state(state) {}

        void operator()(I32 *ref) const {
            luaL_unref(m_state(), LUA_REGISTRYINDEX, *ref);
            delete ref;
        }

      private:
        TE::Lua::State &m_state;
    };
}

TE::Lua::LuaRef::LuaRef(State &state, I32 nativeRef)
    : m_state(state),
      m_nativeRef(new int{nativeRef}, ReFDeleter(state)) {}

TE::Lua::LuaRef::LuaRef(State &state) : LuaRef(state, LUA_REFNIL) {}

void TE::Lua::LuaRef::Push() const { lua_rawgeti(m_state(), LUA_REGISTRYINDEX, *m_nativeRef); }

void TE::Lua::LuaRef::Get() const {
    Push();
    lua_gettable(m_state(), -2);
    lua_remove(m_state(), LuaAbsoluteIndex(m_state, -2));
}

void TE::Lua::TraverseRefs(State &state, const std::vector<LuaRef> &luaRefs) {
    lua_pushvalue(state(), LUA_GLOBALSINDEX);
    for (auto &ref : luaRefs)
        ref.Get();
}
