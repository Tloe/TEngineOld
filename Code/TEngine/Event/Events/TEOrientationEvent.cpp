#include <TEOrientationEvent.h>
#include <TEEventHandler.h>

TE::Event::OrientationEvent::OrientationEvent(TE::Math::Quaternion<F32> &orientation)
    : m_orientation(orientation)
{

}

void TE::Event::OrientationEvent::VisitEventHandler(TE::Event::EventHandler &eventHandler)
{
    eventHandler.HandleEvent(*this);
}

TE::Math::Quaternion<F32> TE::Event::OrientationEvent::GetOrientation()
{
    return m_orientation;
}
