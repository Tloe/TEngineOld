#ifndef TEEVENTHANDLER_H
#define TEEVENTHANDLER_H

#include "TEDataTypes.h"

namespace TE::Event {
  class EventVisitor;
  class ResolutionEvent;
  class TranslationEvent;
  class ScaleEvent;
  class OrientationEvent;
  class EnvironmentUpdateEvent;

  class EventHandler {
  public:
    virtual void HandleEvent(EventVisitor &);
    virtual void HandleEvent(ResolutionEvent &);
    virtual void HandleEvent(TranslationEvent &);
    virtual void HandleEvent(ScaleEvent &);
    virtual void HandleEvent(OrientationEvent &);
    virtual void HandleEvent(EnvironmentUpdateEvent &);
  };
}

#endif
