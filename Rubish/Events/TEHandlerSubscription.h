/**
 *	\file		TEHandlerSubscription.h
 *  \author		Terje Loe
 *  \brief		Defenitions for HandlerSubscription class
 *				!! Events Will be rewritten to use fast delegates and the command pattern (GOF) !!
 */

#ifndef TEHANDLERSUBSCRIPTION_H
#define TEHANDLERSUBSCRIPTION_H

#include <memory>

namespace TE
{
	//Forward declarations
	namespace Events { class EventHandler; }
	namespace Events { class Event; }
	//End forward declarations

	namespace Events
	{
		class HandlerSubscriptionBase
		{
		public:
			virtual	~HandlerSubscriptionBase(){}
			virtual void CallBack(Event& event) = 0;
			virtual bool SameEventHandler(const EventHandler* eventHandler) = 0;
		};

		template <typename EventHandlerT, typename EventT>
		class HandlerSubscription : public HandlerSubscriptionBase
		{
		public:
			typedef void (EventHandlerT::*EventCallback)(EventT&);

			HandlerSubscription(EventHandlerT& eventHandler, EventCallback callback)
				: m_eventHandler(eventHandler), m_callback(callback){}
			
			virtual bool SameEventHandler(const EventHandler* eventHandler)
			{
				return &m_eventHandler == eventHandler;
			}

			void CallBack(Event& event)
			{
				(m_eventHandler.*m_callback)(static_cast<EventT&>(event));
			}
		private:
			EventHandlerT& m_eventHandler;
			EventCallback m_callback;
		};

		typedef std::unique_ptr<HandlerSubscriptionBase> HandlerSubscriptionBaseUPtr;
	}
}

#endif
