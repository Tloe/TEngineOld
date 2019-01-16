#ifndef TEQUEDEVENT_H
#define TEQUEDEVENT_H

#include "TEEventHandler.h"
#include <typeinfo>

namespace TE
{
	namespace Event
	{
		class QuedEventBase
		{
		public:
            virtual ~QuedEventBase(){}

			virtual void HandleEvent(EventHandler* eventHandler) = 0;
			virtual const std::type_info* GetTypeInfo() = 0;
		};

		template <typename EventT>
		class QuedEvent : public QuedEventBase
		{
		public:
			QuedEvent(EventT& event);
			virtual void HandleEvent(EventHandler* eventHandler);
			virtual const std::type_info* GetTypeInfo();

		private:
            EventT m_event;
            const std::type_info* m_typeInfo;
		};

		template <typename EventT>
		TE::Event::QuedEvent<EventT>::QuedEvent( EventT & event )
            : m_event(std::move(event))
			, m_typeInfo(&typeid(event))
		{

		}

		template <typename EventT>
        void TE::Event::QuedEvent<EventT>::HandleEvent( EventHandler* eventHandler )
		{
            eventHandler->HandleEvent(m_event);
		}

		template <typename EventT>
		const std::type_info* TE::Event::QuedEvent<EventT>::GetTypeInfo()
		{
			return m_typeInfo;
		}
	}
}

#endif
