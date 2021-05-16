#include "TEEventVisitor.h"
#include "TEEventHandler.h"

void TE::Event::EventVisitor::VisitEventHandler(EventHandler &eventHandler) {
    eventHandler.HandleEvent(*this);
}
