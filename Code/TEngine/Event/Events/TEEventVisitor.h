#ifndef TEEVENTVISITOR_H
#define TEEVENTVISITOR_H

#include "TEDataTypes.h"

namespace TE {
    namespace Event {
        class EventHandler;
    }

    namespace Event {
        class EventVisitor // Visitor
        {
          public:
            virtual void VisitEventHandler(EventHandler &eventHandler);
        };
    }
}

#endif
