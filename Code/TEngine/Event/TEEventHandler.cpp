#include "TEEventHandler.h"

#include <assert.h>

void TE::Event::EventHandler::HandleEvent( EventVisitor& )
{
    assert(false && "Event handler has not implemented handling for this event");
}

void TE::Event::EventHandler::HandleEvent( ResolutionEvent& )
{
    assert(false && "Event handler has not implemented handling for this event");
}

void TE::Event::EventHandler::HandleEvent(TE::Event::TranslationEvent &)
{
    assert(false && "Event handler has not implemented handling for this event");
}

void TE::Event::EventHandler::HandleEvent(TE::Event::ScaleEvent &)
{
    assert(false && "Event handler has not implemented handling for this event");
}

void TE::Event::EventHandler::HandleEvent(TE::Event::OrientationEvent &)
{
    assert(false && "Event handler has not implemented handling for this event");
}

void TE::Event::EventHandler::HandleEvent(EnvironmentUpdateEvent &)
{
    assert(false && "Event handler has not implemented handling for this event");
}
