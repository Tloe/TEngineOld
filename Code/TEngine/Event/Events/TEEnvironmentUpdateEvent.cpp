#include "TEEnvironmentUpdateEvent.h"
#include "TEEventHandler.h"


TE::Event::EnvironmentUpdateEvent::EnvironmentUpdateEvent(const std::string &name, Core::Variant &value)
    : m_name(name)
    , m_value(value)
{
}

TE::Event::EnvironmentUpdateEvent::EnvironmentUpdateEvent(const std::string &name, Core::Variant value)
    : m_name(name)
    , m_value(value)
{
}

void TE::Event::EnvironmentUpdateEvent::VisitEventHandler(TE::Event::EventHandler &eventHandler)
{
    eventHandler.HandleEvent(*this);
}

std::string &TE::Event::EnvironmentUpdateEvent::GetName()
{
    return m_name;
}

TE::Core::Variant &TE::Event::EnvironmentUpdateEvent::GetValue()
{
    return m_value;
}
