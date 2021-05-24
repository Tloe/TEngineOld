#ifndef TELUAINTERFACE_H
#define TELUAINTERFACE_H

#include "lua.hpp"

namespace TE::Engine {
  class EngineRoot;
}

namespace TE::LUAInterface {
  extern Engine::EngineRoot *engineRoot;

  void SetupInterface(Engine::EngineRoot &engineRoot);
  static int SetDataEngineRoot(lua_State *luaState);
}

#endif
