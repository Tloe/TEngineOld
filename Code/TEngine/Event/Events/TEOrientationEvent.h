#ifndef TEORIENTATIONEVENT_H
#define TEORIENTATIONEVENT_H

#include "TEEventVisitor.h"
#include "TEQuaternion.h"

namespace TE {
    namespace Event {
        class EventHandler;
    }

    namespace Event {
        class OrientationEvent : public EventVisitor {
          public:
            OrientationEvent(Math::Quaternion<F32> &orientation);
            virtual void VisitEventHandler(EventHandler &eventHandler);
            Math::Quaternion<F32> GetOrientation();

          private:
            Math::Quaternion<F32> m_orientation;
        };
    }
}

#endif
