#ifndef TELUANATIVE_H
#define TELUANATIVE_H

#include "TEDataTypes.h"
#include "TELuaHelpers.h"

#include <string>
#include <type_traits>

namespace TE
{
	namespace Lua { class State; }

	namespace Lua
	{
		namespace Detail
		{
			bool ReadStack(Id<bool>, State & state, I32 index = -1);
			I32 ReadStack(Id<I32>, State & state, I32 index = -1);
			U32 ReadStack(Id<U32>, State & state, I32 index = -1);
			F32 ReadStack(Id<F32>, State & state, I32 index = -1);
			F64 ReadStack(Id<F64>, State & state, I32 index = -1);
			std::string ReadStack(Id<std::string>, State & state, I32 index = -1);
		}

		template <typename T>
		using NoRef = typename std::remove_reference<T>::type;

		void Push(State & state);
		void Push(State & state, const bool value);
		void Push(State & state, const I32 value);
		void Push(State & state, const U32 value);
		void Push(State & state, const F32 value);
		void Push(State & state, const F64 value);
		void Push(State & state, const std::string & value);
		void Push(State & state, const char * value);
		
		template <typename T, typename... Ts>
		void Push(State & state, const T value, const Ts... values)
		{
			Push(value);
			Push(values...);
		}

		template <typename T>
		T ReadStack(Id<T> t, State & state, I32 index = -1)
		{
			return Detail::ReadStack(t, state, index);
		}

		template <typename... Ts, std::size_t... N>
		std::tuple<Ts...> ReadStackN(State & state, I32 n, Indices<N...>)
		{

			static std::tuple<NoRef<Ts>...> saved;
			saved = std::make_tuple(ReadStack<NoRef<Ts>>(Id<NoRef<Ts>>{},
				state,
				-(n - static_cast<I32>(N)))...);

			return std::tie(std::get<N>(saved)...);
		}
	}
}

#endif
