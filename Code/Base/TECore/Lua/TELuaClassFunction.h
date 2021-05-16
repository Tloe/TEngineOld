#ifndef TECLASSFUNCTION_H
#define TECLASSFUNCTION_H

#include "TELuaBaseFunction.h"
#include "TELuaHelpers.h"

#include "lua.hpp"

namespace TE {
    namespace Lua {
        class State;
    }

    namespace Lua {
        template <int N, typename ClassT, typename Ret, typename... Args>
        class ClassFunction : public BaseFunction {
            using FunctionType = std::function<Ret(ClassT *, Args...)>;

          public:
            ClassFunction(State &state,
                          const std::string &name,
                          const std::string &metatableName,
                          FunctionType function);
            ClassFunction(State &state,
                          const std::string &name,
                          const std::string &metatableName,
                          Ret (*function)(Args...));

            virtual I32 Execute();

          private:
            ClassT *GetTPointer() const;

            State &m_state;
            std::string m_metatableName;
            FunctionType m_function;
        };

        template <typename ClassT, typename... Args>
        class ClassFunction<0, ClassT, void, Args...> : public BaseFunction {
            using FunctionType = std::function<void(ClassT *, Args...)>;

          public:
            ClassFunction(State &state,
                          const std::string &name,
                          const std::string &metatableName,
                          FunctionType function);
            ClassFunction(State &state,
                          const std::string &name,
                          const std::string &metatableName,
                          void (*function)(Args...));

            virtual I32 Execute();

          private:
            ClassT *GetTPointer() const;

            State &m_state;
            std::string m_metatableName;
            FunctionType m_function;
        };

        template <int N, typename ClassT, typename Ret, typename... Args>
        TE::Lua::ClassFunction<N, ClassT, Ret, Args...>::ClassFunction(State &state,
                                                                       const std::string &name,
                                                                       const std::string &metatableName,
                                                                       FunctionType function)
            : m_state(state),
              m_metatableName(metatableName),
              m_function(function) {
            lua_pushlightuserdata(StateToNative(state), (void *)static_cast<BaseFunction *>(this));
            lua_pushcclosure(StateToNative(state), &LuaDispatcher, 1);
            lua_setfield(StateToNative(state), -2, name.c_str());
        }

        template <int N, typename ClassT, typename Ret, typename... Args>
        TE::Lua::ClassFunction<N, ClassT, Ret, Args...>::ClassFunction(State &state,
                                                                       const std::string &name,
                                                                       const std::string &metatableName,
                                                                       Ret (*function)(Args...))
            : ClassFunction(state, name, metatableName, FunctionType{function}) {
        }

        template <int N, typename ClassT, typename Ret, typename... Args>
        I32 TE::Lua::ClassFunction<N, ClassT, Ret, Args...>::Execute() {
            std::tuple<ClassT *> classT                = std::make_tuple(GetTPointer());
            std::tuple<Args...> variableArgs           = GetArgs<Args...>(m_state);
            std::tuple<ClassT *, Args...> functionArgs = std::tuple_cat(classT, variableArgs);
            Lift(m_function, functionArgs);
            return N;
        }

        template <int N, typename ClassT, typename Ret, typename... Args>
        ClassT *TE::Lua::ClassFunction<N, ClassT, Ret, Args...>::GetTPointer() const {
            ClassT *pointer = static_cast<ClassT *>(luaL_checkudata(StateToNative(m_state), 1, m_metatableName.c_str()));
            lua_remove(StateToNative(m_state), 1);
            return pointer;
        }

        // specialization
        template <typename ClassT, typename... Args>
        TE::Lua::ClassFunction<0, ClassT, void, Args...>::ClassFunction(State &state,
                                                                        const std::string &name,
                                                                        const std::string &metatableName,
                                                                        FunctionType function)
            : m_state(state),
              m_metatableName(metatableName),
              m_function(function) {
            lua_pushlightuserdata(StateToNative(state), (void *)static_cast<BaseFunction *>(this));
            lua_pushcclosure(StateToNative(state), &LuaDispatcher, 1);
            lua_setfield(StateToNative(state), -2, name.c_str());
        }

        template <typename ClassT, typename... Args>
        TE::Lua::ClassFunction<0, ClassT, void, Args...>::ClassFunction(State &state,
                                                                        const std::string &name,
                                                                        const std::string &metatableName,
                                                                        void (*function)(Args...))
            : ClassFunction(state, name, metatableName, FunctionType{function}) {
        }

        template <typename ClassT, typename... Args>
        I32 TE::Lua::ClassFunction<0, ClassT, void, Args...>::Execute() {
            std::tuple<ClassT *> classT                = std::make_tuple(GetTPointer());
            std::tuple<Args...> variableArgs           = GetArgs<Args...>(m_state);
            std::tuple<ClassT *, Args...> functionArgs = std::tuple_cat(classT, variableArgs);
            Lift(m_function, functionArgs);
            return 0;
        }

        template <typename ClassT, typename... Args>
        ClassT *TE::Lua::ClassFunction<0, ClassT, void, Args...>::GetTPointer() const {
            ClassT *pointer = static_cast<ClassT *>(luaL_checkudata(StateToNative(m_state), 1, m_metatableName.c_str()));
            lua_remove(StateToNative(m_state), 1);
            return pointer;
        }
    }
}

#endif
