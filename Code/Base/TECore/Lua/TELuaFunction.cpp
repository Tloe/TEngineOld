#include "TELuaFunction.h"
#include "TELuaState.h"

/*void TE::Detail::SetupFunction(State & state, std::string & name)
{
    lua_pushlightuserdata(state(), static_cast<void *>(static_cast<BaseFunction *>(this)));
    lua_pushcclosure(state(), &LuaDispatcher, 1);
    lua_setglobal(state(), m_name.c_str());
}

void TE::Detail::RemoveFunction(State & state, std::string & name)
{
    lua_pushnil(state());
    lua_setglobal(state(), m_name.c_str());
}
*/
