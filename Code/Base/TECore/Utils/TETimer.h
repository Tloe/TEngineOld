#ifndef TIMER_H
#define TIMER_H

#include "TEDataTypes.h"
#include "TETime.h"

#include <thread>

namespace TE
{
	namespace Time
	{
		class Timer
		{
		public:
			Timer();

			void Restart();
			void Stop();
			bool IsRunning();
			
			U64 GetTime(Units unit);
			U64 GetMilliseconds();
			U64 GetMicroseconds();
			U64 GetNanoseconds();

			void Update();
			U64 GetUpdatedTime(Units unit);
			U64 GetUpdatedMilliseconds();
			U64 GetUpdatedMicroseconds();
			U64 GetUpdatedNanoseconds();
			U64 GetDeltaTime(Units unit);
			U64 GetDeltaMilliseconds();
			U64 GetDeltaMicroseconds();
			U64 GetDeltaNanoseconds();

		private:
			bool m_isRunning;
			std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
			std::chrono::time_point<std::chrono::high_resolution_clock> m_previousUpdate;
			std::chrono::time_point<std::chrono::high_resolution_clock> m_update;
			
		};

		inline void Wait(U64 duration, Units unit = TE::Time::Units::Microseconds)
		{
			switch (unit)
			{
			case TE::Time::Units::Milliseconds:
				std::this_thread::sleep_for(std::chrono::milliseconds(duration));
				break;
			case TE::Time::Units::Microseconds:
				std::this_thread::sleep_for(std::chrono::microseconds(duration));
				break;
			case TE::Time::Units::Nanoseconds:
				std::this_thread::sleep_for(std::chrono::nanoseconds(duration));
				break;
			}
		}

		inline U32 HzToMicroseconds(U32 hz)
		{
			return 1000000 / hz;
		}
	}
}

#endif
