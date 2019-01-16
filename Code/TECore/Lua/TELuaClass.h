#ifndef TELUACLASS_H
#define TELUACLASS_H

#include "TELuaConstructor.h"
#include "TELuaDestructor.h"
#include "TELuaClassFunction.h"

#include <memory>
#include <unordered_map>
#include <functional>

#include <lua.hpp>

namespace
{
	using TypeID = std::reference_wrapper<const std::type_info>;
}

namespace TE
{
	namespace Lua { class State; }
	namespace Lua { class BaseFunction; }

	namespace Lua
	{
		class BaseClass
		{
		public:
			virtual ~BaseClass(){};
		};
		
		template <typename T, typename ConstructorT, typename... Members>
		class Class : public BaseClass
		{
		public:
			Class(State & state, const std::string & className, Members... members);

		private:
			void RegisterConstructor();
			void RegisterDestructor();
			
			template <typename Ret, typename... Args>
			void RegisterMember(const std::string & name, Ret(T::*function)(Args...));

			void RegisterMembers();

			template <typename M, typename... Ms>
			void RegisterMembers(const std::string & name, M member, Ms... members);

			std::string m_metatableName;
			
			std::unique_ptr<ConstructorT> m_constructor;
			std::unique_ptr<Destructor<T>> m_destructor;

			std::unordered_map<std::string, std::unique_ptr<BaseFunction>> m_functions;
			
			State & m_state;
		};

        template <typename T, typename ConstructorT, typename... Members>
        Class<T, ConstructorT, Members...>::Class(State & state, const std::string & className, Members... members)
            : m_metatableName(className + "_tengine")
            , m_state(state)
        {
            luaL_newmetatable(StateToNative(state), m_metatableName.c_str());

            TypeID type = typeid(T);

            lua_pushliteral(StateToNative(state), "TEngine_metatables");
            lua_gettable(StateToNative(state), LUA_REGISTRYINDEX);
            lua_pushlightuserdata(StateToNative(state), const_cast<std::type_info*>(&type.get()));

            lua_pushvalue(StateToNative(state), -3);
            lua_settable(StateToNative(state), -3);

            lua_pop(StateToNative(state), 1);

            RegisterConstructor();
            RegisterDestructor();
            RegisterMembers(members...);

            lua_pushvalue(StateToNative(state), -1);
            lua_setfield(StateToNative(state), -1, "__index");
        }

        template <typename T, typename ConstructorT, typename... Members>
        void Class<T, ConstructorT, Members...>::RegisterConstructor()
        {
            m_constructor.reset(new ConstructorT(m_state, m_metatableName));
        }

        template <typename T, typename ConstructorT, typename... Members>
        void Class<T, ConstructorT, Members...>::RegisterDestructor()
        {
            m_destructor.reset(new Destructor<T>(m_state, m_metatableName));
        }

        template <typename T, typename ConstructorT, typename... Members>
        void Class<T, ConstructorT, Members...>::RegisterMembers()
        {

        }

        template <typename T, typename ConstructorT, typename... Members>
        template <typename Ret, typename... Args>
        void Class<T, ConstructorT, Members...>::RegisterMember(const std::string & name, Ret(T::*function)(Args...))
        {
            m_functions[name] = std::make_unique<ClassFunction<RetCount<Ret>::Count, T, Ret, Args...>>(m_state, name, m_metatableName, function);
        }

        template <typename T, typename ConstructorT, typename... Members>
        template <typename M, typename... Ms>
        void Class<T, ConstructorT, Members...>::RegisterMembers(const std::string & name, M member, Ms... members)
        {
            RegisterMember(name, member);
            RegisterMembers(members...);
        }
    }
}

#endif
