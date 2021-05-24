#ifndef TESCALEEVENT_H
#define TESCALEEVENT_H

#include "TEEventVisitor.h"
#include "TEVector3D.h"

namespace TE::Event {
  class EventHandler;

  class ScaleEvent : public EventVisitor {
  public:
    ScaleEvent(Math::Vector3D<F32> &scale);
    virtual void VisitEventHandler(EventHandler &eventHandler);
    Math::Vector3D<F32> GetScale();

  private:
    Math::Vector3D<F32> m_scale;
  };
}

#endif
