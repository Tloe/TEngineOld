#include <TEEVentHandler.h>


template<class EventHandlerT, class EventT>
TE::EventSubscription<EventHandlerT, EventT>::EventSubscription( EventHandlerT *eventHandler, EventCallback *callback ) : m_eventHandler(eventHandler), m_eventCallback(callback)
{
	TheEventManager::registerSubscription(&type_info(EventT),this);
}

template<class EventHandlerT, class EventT>
TE::EventSubscription<EventHandlerT, EventT>::~EventSubscription()
{
	TheEventManager::unregisterSubscription(&type_info(EventT),this);
}

template<class EventHandlerT, class EventT>
void TE::EventSubscription<EventHandlerT, EventT>::execute( const Event &event )
{
	(m_eventHandler->*m_eventCallback)(static_cast<EventT*>(&event));
}
