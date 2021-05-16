#ifndef TELUAHELPERS_H
#define TELUAHELPERS_H

#include "TEDataTypes.h"

#include <vector>

#include <lua.hpp>

namespace TE {
    namespace Lua {
        class State;
    }

    namespace Lua {
        I32 LuaAbsoluteIndex(State &state, I32 index);
        void LuaSwap(State &state, I32 index0, I32 index1);
        void LuaSwap(State &state);
        void CreateTableInRegistry(State &state, const std::string &name);
        lua_State *StateToNative(State &state);

        template <std::size_t... Is>
        struct Indices {};

        // Recursively inherits from itself until...
        template <std::size_t N, std::size_t... Is>
        struct IndicesBuilder : IndicesBuilder<N - 1, N - 1, Is...> {};

        // The base case where we define the type tag
        template <std::size_t... Is>
        struct IndicesBuilder<0, Is...> {
            using Type = Indices<Is...>;
        };

        template <typename T>
        struct Id {};
    }
}

#endif
