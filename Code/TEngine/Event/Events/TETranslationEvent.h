#ifndef TETRANSLATIONEVENT_H
#define TETRANSLATIONEVENT_H

#include "TEEventVisitor.h"
#include "TEVector3D.h"

namespace TE::Event {
  class EventHandler;

  class TranslationEvent : public EventVisitor {
  public:
    TranslationEvent(Math::Vector3D<F32> &translation);
    virtual void VisitEventHandler(EventHandler &eventHandler);
    const Math::Vector3D<F32> &GetTranslation();

  private:
    Math::Vector3D<F32> m_translation;
  };
}

#endif
