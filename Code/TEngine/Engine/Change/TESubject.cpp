#include "TESubject.h"
#include "TEObserver.h"

#include <assert.h>
#include <algorithm>

void TE::Engine::Subject::AttachObserver( Observer& observer, Bitmask64 changeBits )
{
	ObserverSubscription observerSubscription;
	observerSubscription.observer = &observer;
	observerSubscription.subscribeBits = changeBits;
	std::lock_guard<std::mutex> lock(m_mutex);
    m_observerSubscriptions.emplace_back(observerSubscription);
}

void TE::Engine::Subject::DetachObserver( Observer& observer )
{
    std::lock_guard<std::mutex> lock(m_mutex);
    auto findItr = std::find_if(std::begin(m_observerSubscriptions), std::end(m_observerSubscriptions),
                 [&observer](ObserverSubscription & observerSubscription)
                 {
                    return &observer == observerSubscription.observer;
                 });

    m_observerSubscriptions.erase(findItr);
}

void TE::Engine::Subject::PostSubjectChanges( Bitmask64 changeBits )
{
    for (auto& itr : m_observerSubscriptions)
    {
        if (itr.subscribeBits & changeBits)
        {
            itr.observer->OnSubjectChange(this, changeBits);
        }
    }
}

TE::Engine::Change::ChangeDataPtrVar TE::Engine::Subject::GetChangeData(Bitmask64 changeBits)
{
    assert("Derrived can implement this");
    return TE::Engine::Change::ChangeDataPtrVar();
}

TE::Engine::Subject::Priority TE::Engine::Subject::GetPriority() const
{
    return Priority::Level0;
}

I32 TE::Engine::Subject::GetObjectId() const
{
    return -1;
}
