#include <TEEventScheduler.h>
#include <functional>
#include <TEEvent.h>
#include <TETimedEvent.h>
#include <assert.h>

TE::Events::EventScheduler::EventScheduler()
	:
	m_time(0.0),
	m_lastUpdateTime(0.0)
{
	RegisterEventCallback(*this, &EventScheduler::OnTimedEvent);
}

TE::Events::EventScheduler::~EventScheduler()
{
	UnRegisterEventCallback(&EventScheduler::OnTimedEvent);
}

void TE::Events::EventScheduler::OnTimedEvent( TimedEvent& event )
{
	switch (event.GetTimedType())
	{
	case TimedEvent::TIMEDTYPE_ENDFRAME:
		m_endFrameEvents.push_back(std::move(event.GetEvent()));
		break;
	case TimedEvent::TIMEDTYPE_NEXTFRAME:
		m_beginFrameEvents.push_back(std::move(event.GetEvent()));
		break;
	case TimedEvent::TIMEDTYPE_DELAYED:
		m_timedEvents.insert(std::move(std::make_pair(m_time + event.GetDelayInSeconds(), std::move(event.GetEvent()))));
		break;
	}
}

void TE::Events::EventScheduler::BeginFrame( Real dt )
{
	if (!m_beginFrameEvents.empty())
	{
		std::for_each(m_beginFrameEvents.begin(), m_beginFrameEvents.end(), std::bind(&Event::Invoke, std::placeholders::_1));
		m_beginFrameEvents.clear();
	}

	m_time += dt;
	
	if (m_time - m_lastUpdateTime >= 10.0)
	{
		DoTimedEvents();
		m_lastUpdateTime = m_time;
	}
}

void TE::Events::EventScheduler::EndFrame()
{
	if(!m_endFrameEvents.empty())
	{
		std::for_each(m_endFrameEvents.begin(), m_endFrameEvents.end(), std::bind(&Event::Invoke, std::placeholders::_1));
		m_endFrameEvents.clear();
	}
}

void TE::Events::EventScheduler::DoTimedEvents()
{
	if (m_timedEvents.empty()) return;

	EventPtrMap::iterator current = m_timedEvents.begin();;
	EventPtrMap::const_iterator last = m_timedEvents.end();
	while(current != last && current->first < m_time)
	{
		assert(current->second); //Maybe just erase if null?
		current->second->Invoke();
		m_timedEvents.erase(current++);
	}
}

