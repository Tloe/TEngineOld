#ifndef TEEVENTREGISTRY_H
#define TEEVENTREGISTRY_H

#include "TEDataTypes.h"
#include "TEEventVisitor.h"
#include "TEQuedEvent.h"

#include <memory>
#include <mutex>
#include <set>
#include <typeinfo>
#include <unordered_map>
#include <vector>

namespace TE {
    namespace Event {
        class EventHandler;
    }

    namespace Event {
        class EventManager {
          public:
            template <typename EventT, typename EventHandlerT>
            void Subscribe(EventHandlerT *eventHandler);
            template <typename EventT, typename EventHandlerT>
            void UnSubscribe(EventHandlerT *eventHandler);

            template <typename EventT>
            void QueEvent(EventT &event);
            void HandleQuedEvents();

          private:
            typedef std::set<EventHandler *> SubscriptionSet;
            typedef std::unordered_map<const std::type_info *, SubscriptionSet> SubscriptionsMap;
            typedef std::unique_ptr<QuedEventBase> QuedEventBaseUPtr;
            typedef std::vector<QuedEventBaseUPtr> EventQue;

            SubscriptionsMap m_subscriptionMap;
            std::mutex m_eventQueMutex;
            EventQue m_eventQue;
        };

        template <typename EventT>
        void TE::Event::EventManager::QueEvent(EventT &event) {
            std::lock_guard<std::mutex> lock(m_eventQueMutex);
            m_eventQue.emplace_back(std::make_unique<QuedEvent<EventT>>(event));
        }

        template <typename EventT, typename EventHandlerT>
        void TE::Event::EventManager::Subscribe(EventHandlerT *eventHandler) {
            m_subscriptionMap[&typeid(EventT)].insert(eventHandler);
        }

        template <typename EventT, typename EventHandlerT>
        void TE::Event::EventManager::UnSubscribe(EventHandlerT *eventHandler) {
            const auto &findItr = m_subscriptionMap.find(&typeid(EventT));
            if (findItr != m_subscriptionMap.end()) {
                findItr->second.erase(eventHandler);
            }
        }
    }
}

#endif
