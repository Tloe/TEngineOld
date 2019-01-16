#include "TELuaInterface.h"
#include "TEEngine.h"

TE::Engine::EngineRoot * TE::LUAInterface::engineRoot;

void TE::LUAInterface::SetupInterface(Engine::EngineRoot & engineRoot)
{
	LUAInterface::engineRoot = &engineRoot;

	luaL_Reg functions[] =
	{
		{ "SetData", SetDataEngineRoot },
		{ NULL, NULL }
	};
	
    //luaL_newlib("",);
}

static int TE::LUAInterface::SetDataEngineRoot(lua_State * luaState)
{
	return -1;
}

