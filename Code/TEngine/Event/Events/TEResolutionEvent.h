#ifndef TERESOLUTIONEVENT_H
#define TERESOLUTIONEVENT_H

#include "TEEventVisitor.h"

namespace TE::Event {
  class EventHandler;

  class ResolutionEvent : public EventVisitor {
  public:
    ResolutionEvent(bool fullscreen,
                    bool updateViewport,
                    I32 width,
                    I32 height,
                    I32 viewportWidth  = 640,
                    I32 viewportHeight = 480,
                    I32 positionX      = -1,
                    I32 positionY      = -1);

    virtual void VisitEventHandler(EventHandler &eventHandler);

    bool GetFullscreen();
    bool GetUpdateViewport();
    I32 GetWidth();
    I32 GetHeight();
    I32 GetViewportWidth();
    I32 GetViewportHeight();
    I32 GetPositionX();
    I32 GetPositionY();

  private:
    bool m_fullscreen;
    bool m_updateViewport;
    I32 m_width;
    I32 m_height;
    I32 m_viewportWidth;
    I32 m_viewportHeight;
    I32 m_positionX;
    I32 m_positionY;
  };
}

#endif
