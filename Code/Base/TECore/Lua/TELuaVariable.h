#ifndef TELUAVARIABLE_H
#define TELUAVARIABLE_H

#include "TEDataTypes.h"
#include "TELuaNative.h"
#include "TELuaRef.h"
#include "TELuaStackReseter.h"
#include "TELuaState.h"

#include <lua.hpp>

#include <string>
#include <tuple>
#include <vector>

#ifdef RegisterClass
#undef RegisterClass
#endif

namespace TE {
    namespace Lua {
        class Table;
    }

    namespace Lua {
        class Variable {
          public:
            Variable(State &state, LuaRef keyRef, const std::vector<LuaRef> &keyPath = std::vector<LuaRef>());

            Variable operator[](const std::string &key) const;
            Variable operator[](const char *key) const;
            Variable operator[](const I32 key) const;

            template <typename... Args>
            const Variable operator()(Args &&...args);

            operator bool() const;
            operator I32() const;
            operator U32() const;
            operator F32() const;
            operator std::string() const;

            template <typename... Ts>
            operator std::tuple<Ts...>() const;

            void operator=(bool value) const;
            void operator=(I32 value) const;
            void operator=(U32 value) const;
            void operator=(F32 value) const;
            void operator=(const std::string &value) const;
            void operator=(const char *value) const;

            template <typename ClassT, typename... CTorArgs, typename... Members>
            void SetClass(Members... members);

          private:
            void Call(I32 returnCount) const;
            void Get() const;
            void CheckCreateTable() const;
            template <typename T>
            void Store(T value) const;
            std::string FieldName() const;

            State &m_state;
            std::vector<LuaRef> m_keyPath;
            LuaRef m_keyRef;
            mutable bool m_callTriggered;
            std::vector<LuaRef> m_callArgs;
        };

        template <typename... Args>
        const Variable Variable::operator()(Args &&...args) {
            Variable returnVariable(*this);
            returnVariable.m_callTriggered = true;
            returnVariable.m_callArgs      = RefsFromTs(m_state, args...);

            return returnVariable;
        }

        template <typename... Ts>
        Variable::operator std::tuple<Ts...>() const {
            constexpr std::size_t tsCount = sizeof...(Ts);

            StackReseter stackReseter(m_state);
            Get();
            if (m_callTriggered)
                Call(tsCount);

            return ReadStackN<Ts...>(m_state, tsCount, typename IndicesBuilder<tsCount>::Type());
        }

        template <typename ClassT, typename... CTorArgs, typename... Members>
        void Variable::SetClass(Members... members) {
            StackReseter stackReseter(m_state);
            TraverseRefs(m_state, m_keyPath);

            m_keyRef.Push();
            std::string name = ReadStack<std::string>(Id<std::string>{}, m_state);

            auto memberTuple = std::make_tuple(members...);
            typename IndicesBuilder<sizeof...(Members)>::Type indices;

            m_state.RegisterClass<ClassT, CTorArgs...>(name, memberTuple, indices);

            lua_settable(m_state(), -3);
        }

        template <typename T>
        void Variable::Store(T value) const {
            StackReseter stackReseter(m_state);
            TraverseRefs(m_state, m_keyPath);
            m_keyRef.Push();
            Push(m_state, value);
            lua_settable(m_state(), -3);
        }
    }
}

#endif
