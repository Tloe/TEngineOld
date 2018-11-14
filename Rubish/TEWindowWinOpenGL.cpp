#include <TEWindowWinOpenGL.h>
#include <GL/glew.h>
#include <GL/glu.h>
#include "TEContextWinOpenGL.h"
#include "TEWindow.h"

TE::Context::APIPlatformWindow::APIPlatformWindow()
{
}

TE::Context::APIPlatformWindow::~APIPlatformWindow()
{

}

void TE::Context::APIPlatformWindow::Init(Render::APIContext& apiContext, Window& window)
{
	WindowWin::Init(window);

	PIXELFORMATDESCRIPTOR pfd;
	int format;

	// get the device context (DC)
	m_hdc = GetDC( GetHWND() );

	// set the pixel format for the DC
	ZeroMemory( &pfd, sizeof( pfd ) );
	pfd.nSize = sizeof( pfd );
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;
	format = ChoosePixelFormat( m_hdc, &pfd );
	SetPixelFormat( m_hdc, format, &pfd );

	// create and enable the render context (RC)
	m_hrc = wglCreateContext( m_hdc );
	wglMakeCurrent( m_hdc, m_hrc );

	glViewport(0, 0, window.GetWidth(), window.GetHeight());
}

void TE::Context::APIPlatformWindow::Cleanup( Render::APIContext& apiContext )
{
	if(!wglMakeCurrent( NULL, NULL ) ||
		!wglDeleteContext( m_hrc ) ||
		!ReleaseDC( GetHWND(), m_hdc ))
	{
		//LOG FATAL ERROR
		exit(0);
	}
}

void TE::Context::APIPlatformWindow::BeginFrame()
{
	WindowWin::BeginFrame();
}

void TE::Context::APIPlatformWindow::EndFrame()
{
	SwapBuffers(m_hdc);
}

TE::Context::Window& TE::Context::APIPlatformWindow::GetWindowRef()
{
	return WindowWin::GetWindowRef();
}

