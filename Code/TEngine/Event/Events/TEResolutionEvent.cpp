#include "TEResolutionEvent.h"
#include "TEEventHandler.h"

TE::Event::ResolutionEvent::ResolutionEvent( bool fullscreen, bool updateViewport, I32 width, I32 height, I32 viewportWidth, I32 viewportHeight, I32 positionX, I32 positionY )
	: m_fullscreen(fullscreen)
	, m_updateViewport(updateViewport)
	, m_width(width)
	, m_height(height)
	, m_viewportWidth(viewportWidth)
	, m_viewportHeight(viewportHeight)
    , m_positionX(positionX)
    , m_positionY(positionY)
{

}

void TE::Event::ResolutionEvent::VisitEventHandler(EventHandler & eventHandler )
{
    eventHandler.HandleEvent(*this);
}

bool TE::Event::ResolutionEvent::GetFullscreen()
{
	return m_fullscreen;
}

bool TE::Event::ResolutionEvent::GetUpdateViewport()
{
	return m_updateViewport;
}

I32 TE::Event::ResolutionEvent::GetWidth()
{
	return m_width;
}

I32 TE::Event::ResolutionEvent::GetHeight()
{
	return m_height;
}

I32 TE::Event::ResolutionEvent::GetViewportWidth()
{
	return m_viewportWidth;
}

I32 TE::Event::ResolutionEvent::GetViewportHeight()
{
    return m_viewportHeight;
}

I32 TE::Event::ResolutionEvent::GetPositionX()
{
    return m_positionX;
}

I32 TE::Event::ResolutionEvent::GetPositionY()
{
    return m_positionY;
}

