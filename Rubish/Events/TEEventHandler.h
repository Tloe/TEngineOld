/**
 *	\file		TEEventHandler.h
 *  \author		Terje Loe
 *  \brief		Defenitions for EventHandler class
 *				!! Events Will be rewritten to use fast delegates and the command pattern (GOF) !!
 */

#ifndef TEEVENTHANDLER_H
#define TEEVENTHANDLER_H

#include <vector>
#include <algorithm>
#include <TEHandlerSubscription.h>
#include <typeinfo>
#include <TEEvent.h>

namespace TE
{
	namespace Events
	{
		class EventHandler
		{
		public:
			EventHandler();

			virtual ~EventHandler();
		protected:
			template<typename EventHandlerT, typename EventT>
			void RegisterEventCallback(EventHandlerT& eventHandler, void (EventHandlerT::*eventCallback)(EventT&));

			template<typename EventHandlerT, typename EventT>
			void UnRegisterEventCallback(void (EventHandlerT::*eventCallback)(EventT&));
		};
		
		template<typename EventHandlerT, typename EventT>
		void EventHandler::RegisterEventCallback( EventHandlerT& eventHandler, void (EventHandlerT::*eventCallback)(EventT&) )
		{
			HandlerSubscriptionBaseUPtr subscription(new HandlerSubscription<EventHandlerT, EventT>(eventHandler, eventCallback));
			Event::RegisterSubscription(&typeid(EventT), this, subscription);
		};


		template<typename EventHandlerT, typename EventT>
		void EventHandler::UnRegisterEventCallback( void (EventHandlerT::*eventCallback)(EventT&) )
		{
			Event::UnRegisterSubscription(&typeid(EventT), this);
		}

	}
}

#endif
