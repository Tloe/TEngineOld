/**
 *	\file		TEEvent.h
 *  \author		Terje Loe
 *  \brief		Defenitions for the base Event class
 *				!! Events Will be rewritten to use fast delegates and the command pattern (GOF) !!
 */

#ifndef TEEVENT_H
#define TEEVENT_H

#include <memory>
#include <list>
#include <typeinfo>
#include <unordered_map>
#include <vector>

namespace TE
{
	//Forward declarations
    namespace Events { class HandlerSubscriptionBase; typedef std::unique_ptr<HandlerSubscriptionBase> HandlerSubscriptionBaseUPtr; }
	namespace Events { class EventHandler; }
	//End forward declarations

	namespace Events
	{
		class Event
		{
		private:
			typedef std::list<HandlerSubscriptionBaseUPtr> SubscriptionList;
			typedef std::unordered_map<const std::type_info*, SubscriptionList> SubscriptionsMap;
		public:
			explicit Event(unsigned id) : m_eventId(id){}

			virtual ~Event(){}

			void Invoke();

			unsigned GetEventId() const;
			static void RegisterSubscription(const std::type_info* eventTypeInfoPtr, const EventHandler* eventHandler, HandlerSubscriptionBaseUPtr& subscription);
			static void UnRegisterSubscription(const std::type_info* eventTypeInfoPtr, const EventHandler* eventHandler);
			static SubscriptionsMap& GetSubscriptionsMap();
		private:
			unsigned		m_eventId;
		};

		typedef std::unique_ptr<Event> EventUPtr;
	}
}
#endif
