#ifndef TEEVENTSUBSCRIPTION_H
#define TEEVENTSUBSCRIPTION_H

#include <TEEvent.h>
#include <TEEventManager.h>

namespace TE
{
	class EventSubscriptionBase
	{
	public:
		virtual ~EventSubscriptionBase(){}
		virtual void CallBack(Event& event) = 0;
	};

	template<class EventHandlerT, class EventT>
	class EventSubscription : public EventSubscriptionBase
	{
	public:
		typedef void (EventHandlerT::*EventCallback)(EventT&);

		EventSubscription(unsigned eventId ,EventHandlerT *eventHandler, EventCallback callback)
			: m_eventId(eventId), m_eventHandler(eventHandler), m_eventCallback(callback)
		{
			TheEventManager.RegisterSubscription(eventId,this);
		}

		~EventSubscription()
		{
			TheEventManager.UnregisterSubscription(m_eventId,this);
		}

		EventSubscription(const EventSubscription &src)
		{
			m_eventId = src.m_eventId;
			m_eventHandler = src.m_eventHandler;
			m_eventCallback = src.m_eventCallback;
		}

		EventSubscription& operator=(const EventSubscription &rhs)
		{
			if (&rhs == this) return *this;

			m_eventId = rhs.m_eventId;
			m_eventHandler = rhs.m_eventHandler;
			m_eventCallback = rhs.m_eventCallback;

			return *this;
		}

		void CallBack(Event &event)
		{
			(m_eventHandler->*m_eventCallback)(static_cast<EventT&>(event));
		}
	private:
		unsigned m_eventId;
		EventHandlerT *m_eventHandler;
		EventCallback m_eventCallback;
	};
}

#endif
