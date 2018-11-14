#ifndef TETIMEDEVENT_H
#define TETIMEDEVENT_H

#include <TEEvent.h>
#include "TEEventScheduler.h"

namespace TE
{
	namespace Events
	{
		enum
		{
			tekTimeEvent = 'time'
		};

		class TimedEvent : public Event
		{
		public:
			enum
			{
				TIMEDTYPE_ENDFRAME,
				TIMEDTYPE_NEXTFRAME,
				TIMEDTYPE_DELAYED
			};

			TimedEvent(EventUPtr& event, I32 timedType, I32 delayInSeconds = 0)
				:
				Event(tekTimeEvent),
				m_event(std::move(event)),
				m_timedType(timedType),
				m_delayInSeconds(delayInSeconds)
			{}

			EventUPtr& GetEvent()
			{
				return m_event;
			}

			I32 GetDelayInSeconds()
			{
				return m_delayInSeconds;
			}

			I32 GetTimedType()
			{
				return m_timedType;
			}
		private:
			EventUPtr m_event;
			I32 m_timedType;
			I32 m_delayInSeconds;
		};
	}
}

#endif