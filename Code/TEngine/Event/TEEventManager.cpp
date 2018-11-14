#include "TEEventManager.h"
#include "TEEventHandler.h"
#include "TEEventVisitor.h"

void TE::Event::EventManager::HandleQuedEvents()
{
	std::lock_guard<std::mutex> lock(m_eventQueMutex);
    for (QuedEventBaseUPtr& currentEvent : m_eventQue)
	{
        const auto& findItr = m_subscriptionMap.find(currentEvent->GetTypeInfo());

		if (findItr != m_subscriptionMap.end())
		{
			for (EventHandler* handler : findItr->second)
			{
                currentEvent->HandleEvent(handler);
			}
		}
	}

	m_eventQue.clear();
}
