#ifndef TELUACONSTRUCTOR_H
#define TELUACONSTRUCTOR_H

#include "TELuaBaseFunction.h"

#include <string>
#include <tuple>

#include "lua.hpp"

namespace TE {
    namespace Lua {
        class State;
    }

    namespace Lua {
        template <typename ClassT, typename... Args>
        class Constructor : public BaseFunction {
          public:
            Constructor(State &state, const std::string &metatableName);

            virtual I32 Execute();

          private:
            using ConstructorType = std::function<void(lua_State *, Args...)>;

            State &m_state;
            ConstructorType m_constructor;
        };

        template <typename ClassT, typename... Args>
        Constructor<ClassT, Args...>::Constructor(State &state, const std::string &metatableName)
            : m_state(state),
              m_constructor([metatableName](lua_State *nativeState, Args... args) {
                  void *memory = lua_newuserdata(nativeState, sizeof(ClassT));
                  new (memory) ClassT(args...);
                  luaL_getmetatable(nativeState, metatableName.c_str());
                  lua_setmetatable(nativeState, -2);
              }) {
            lua_pushlightuserdata(StateToNative(m_state), (void *)static_cast<BaseFunction *>(this));
            lua_pushcclosure(StateToNative(m_state), LuaDispatcher, 1);
            lua_setfield(StateToNative(m_state), -2, "new");
        }

        template <typename ClassT, typename... Args>
        I32 Constructor<ClassT, Args...>::Execute() {
            std::tuple<Args...> variableArgs = GetArgs<Args...>(m_state);
            auto functionArgs                = std::tuple_cat(std::make_tuple(StateToNative(m_state)), variableArgs);
            Lift(m_constructor, functionArgs);

            return 1;
        }
    }
}

#endif
