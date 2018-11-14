#ifndef TEEVENTSCHEDULER_H
#define TEEVENTSCHEDULER_H

#include <TEEventHandler.h>
#include <TEDataTypes.h>
#include <map>

namespace TE
{
	//Forward declarations
	namespace Events { class TimedEvent; } 
	namespace Events { class Event; typedef std::unique_ptr<Event> EventUPtr; } 
	//End forward declarations

	namespace Events
	{
		class EventScheduler : public EventHandler
		{
		public:
			EventScheduler();
			~EventScheduler();

			void OnTimedEvent(TimedEvent& event);

			void BeginFrame(Real dt);

			void EndFrame();
		private:
			void DoTimedEvents();

			typedef std::vector<EventUPtr> EventPtrVec;
			typedef std::map<Real, EventUPtr> EventPtrMap;

			Real m_time;
			Real m_lastUpdateTime;
			EventPtrVec m_beginFrameEvents;
			EventPtrVec m_endFrameEvents;
			EventPtrMap m_timedEvents;
		};
	}
}

#endif