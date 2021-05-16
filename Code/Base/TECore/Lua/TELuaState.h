#ifndef TELUASTATE_H
#define TELUASTATE_H

#include <TELuaClass.h>
#include <TELuaFunction.h>

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <lua.hpp>

namespace TE {
    namespace Core {
        class Variant;
    }
    namespace Lua {
        class Table;
    }
    namespace Lua {
        class Variable;
    }
    namespace Lua {
        class State;
    }
    namespace IO {
        class FileIO;
    }

    namespace Lua {
        class State {
          public:
            State(IO::FileIO &fileIO);
            State(const State &other) = delete;
            State &operator=(const State &rhs) = delete;
            State(State &&rhs);
            ~State();

            lua_State *operator()() { return m_nativeState; }

            bool operator()(std::string &code);

            Variable operator[](const std::string &key);
            Variable operator[](I32 key);

            void RunFile(IO::FileIO &fileIO, const std::string &filePath);
            void RunDataBuffer(std::vector<U8> &dataBuffer, const std::string &bufferName);

            template <typename Ret, typename... Args>
            void Register(const std::string &name, std::function<Ret(Args...)> func);

            template <typename Ret, typename... Args>
            void Register(const std::string &name, Ret (*func)(Args...));

            std::string StackOutputString();
            void DebugStack();
            void DEBUGPrintTable(Table &luaTable);

            template <typename ClassT, typename... CTorArgs, typename... Members, size_t... N>
            void RegisterClass(const std::string &name, std::tuple<Members...> members, Indices<N...>);

          private:
            void AddCustomLoader(IO::FileIO &fileIO);
            bool LoadBuffer(const char *buffer, size_t size, std::string name);
            bool CallBuffer();

            std::unordered_map<std::string, std::unique_ptr<BaseClass>> m_classes;
            std::unordered_map<std::string, std::unique_ptr<BaseFunction>> m_functions;
            lua_State *m_nativeState;
        };

        template <typename Ret, typename... Args>
        void State::Register(const std::string &name, std::function<Ret(Args...)> func) {
            m_functions[name] = std::unique_ptr<BaseFunction>(
                new Function<RetCount<Ret>::Count, Ret, Args...>(*this, name, func));
        }

        template <typename Ret, typename... Args>
        void State::Register(const std::string &name, Ret (*func)(Args...)) {
            m_functions[name] = std::unique_ptr<BaseFunction>(
                new Function<RetCount<Ret>::Count, Ret, Args...>(*this, name, func));
        }

        template <typename ClassT, typename... CTorArgs, typename... Members, size_t... N>
        void State::RegisterClass(const std::string &name, std::tuple<Members...> members, Indices<N...>) {
            m_classes.emplace(std::make_pair(name, std::make_unique<Class<ClassT, Constructor<ClassT, CTorArgs...>, Members...>>(*this,
                                                                                                                                 name,
                                                                                                                                 std::get<N>(members)...)));
        }
    }
}

#endif
