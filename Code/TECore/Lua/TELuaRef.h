#ifndef TELUAREF_H
#define TELUAREF_H

#include "TEDataTypes.h"
#include "TELuaState.h"
#include "TELuaHelpers.h"
#include "TELuaNative.h"

#include <vector>
#include <memory>

namespace TE
{
	namespace Lua { class LuaRef; }

	namespace Lua
	{
		namespace Detail
		{
			template <typename... Ts>
			void RecursiveRefsFromT(TE::Lua::State & state, std::vector<TE::Lua::LuaRef> & refs) {}

			template <typename T, typename... Ts>
			void RecursiveRefsFromT(TE::Lua::State & state, std::vector<TE::Lua::LuaRef> & refs, T head, Ts... tail)
			{
				refs.emplace_back(TE::Lua::RefFromT(state, head));
				RecursiveRefsFromT(state, refs, tail...);
			}
		}

		class LuaRef
		{
		public:
			LuaRef(State & state, I32 nativeRef);
			LuaRef(State & state);

			void Push() const;
			void Get() const;
		private:
			State & m_state;
			std::shared_ptr<I32> m_nativeRef;
		};

		void TraverseRefs(State & state, const std::vector<LuaRef> & luaRefs);

		template <typename T>
		LuaRef RefFromT(State & state, T& value)
		{
			Push(state, value);
			return LuaRef(state, luaL_ref(state(), LUA_REGISTRYINDEX));
		}

		template <typename... Ts>
		std::vector<TE::Lua::LuaRef> RefsFromTs(State & state, Ts&... values)
		{
			std::vector<LuaRef> luaRefs;
			luaRefs.reserve(sizeof...(Ts));

			Detail::RecursiveRefsFromT(state, luaRefs, values...);
			return luaRefs;
		}
	}
}

#endif
