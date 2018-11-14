#include "TEScaleEvent.h"
#include "TEEventHandler.h"

TE::Event::ScaleEvent::ScaleEvent(TE::Math::Vector3D<F32> &scale)
    : m_scale(scale)
{
}

void TE::Event::ScaleEvent::VisitEventHandler(TE::Event::EventHandler &eventHandler)
{
    eventHandler.HandleEvent(*this);
}

TE::Math::Vector3D<F32> TE::Event::ScaleEvent::GetScale()
{
    return m_scale;
}
