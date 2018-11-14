#include <TEEvent.h>
#include <TEHandlerSubscription.h>
#include <algorithm>
#include <typeinfo>

unsigned TE::Events::Event::GetEventId() const
{
	return m_eventId;
}

void TE::Events::Event::Invoke()
{
	SubscriptionsMap::iterator mapItr = GetSubscriptionsMap().find(&typeid(*this));
	if (mapItr != GetSubscriptionsMap().end())
	{
		SubscriptionList::iterator listItr = mapItr->second.begin();
		for (; listItr != mapItr->second.end(); ++listItr)
		{
			(*listItr)->CallBack(*this);
		}
	}
}


void TE::Events::Event::RegisterSubscription(const std::type_info* eventTypeInfoPtr, const EventHandler* eventHandler, HandlerSubscriptionBaseUPtr& subscription)
{
	bool regNewSubs = false;
	SubscriptionsMap::iterator mapItr = GetSubscriptionsMap().find(eventTypeInfoPtr);

	if (mapItr != GetSubscriptionsMap().end())
	{
		SubscriptionList::iterator listItr = mapItr->second.begin();
		while(listItr != mapItr->second.end())
		{
			if ((*listItr)->SameEventHandler(eventHandler))
			{
				if (mapItr->second.size() == 1)
					GetSubscriptionsMap().erase(mapItr);
				else 
					mapItr->second.erase(listItr);

				break;
			}
			++listItr;
		}
	}

	GetSubscriptionsMap()[eventTypeInfoPtr].push_back(std::move(subscription));
}

void TE::Events::Event::UnRegisterSubscription(const std::type_info* eventTypeInfoPtr, const EventHandler* eventHandler)
{
	SubscriptionsMap::iterator mapItr = GetSubscriptionsMap().find(eventTypeInfoPtr);
	if (mapItr != GetSubscriptionsMap().end())
	{
		GetSubscriptionsMap().erase(mapItr);
	}
	/*

	if (mapItr != GetSubscriptionsMap().end())
	{
		Subscriptions::iterator listItr = mapItr->second.begin();
		while(listItr != mapItr->second.end())
		{
			if ((*listItr)->SameEventHandler(eventHandler))
			{
				if (mapItr->second.size() == 1)
				{
					//mapItr->second.clear();
					GetSubscriptionsMap().erase(mapItr);
				}
				else 
				{
					mapItr->second.erase(listItr);
				}

				break;
			}
			++listItr;
		}
	}*/
}

TE::Events::Event::SubscriptionsMap& TE::Events::Event::GetSubscriptionsMap()
{
	//Static memory so its ok to "leak" as OS will take care of it when it exits
	static SubscriptionsMap* subscriptionMap = new SubscriptionsMap;
	return *subscriptionMap;
}
