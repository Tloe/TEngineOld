/*
#include <TEWindowLinuxOgl.h>

#if TELINUX

TE::Render::WindowLinuxOgl::WindowLinuxOgl( const WindowInf& winInf ) : Window(winInf)
{

}

TE::Render::WindowLinuxOgl::~WindowLinuxOgl()
{

}

bool TE::Render::WindowLinuxOgl::Initialize()
{
	return InitWindow() && InitContext();
}

bool TE::Render::WindowLinuxOgl::DeInitialize()
{
	glXMakeCurrent(m_dpy, None, NULL);
	glXDestroyContext(m_dpy, m_glc);
	XDestroyWindow(m_dpy, m_window);
	XCloseDisplay(m_dpy);

	return true;
}

void TE::Render::WindowLinuxOgl::NextFrame()
{
	//XNextEvent(m_dpy, m_xev);

	glXSwapBuffers(m_dpy, m_window);
}

void TE::Render::WindowLinuxOgl::TestDrawFunc()
{
	glViewport(0, 0, GetWindowInfo().width, GetWindowInfo().height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1., 1., -1., 1., 1., 20.);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0., 0., 10., 0., 0., 0., 0., 1., 0.);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_QUADS);
	glColor3f(1., 0., 0.); glVertex3f(-.75, -.75, 0.);
	glColor3f(0., 1., 0.); glVertex3f( .75, -.75, 0.);
	glColor3f(0., 0., 1.); glVertex3f( .75,  .75, 0.);
	glColor3f(1., 1., 0.); glVertex3f(-.75,  .75, 0.);
	glEnd();

	NextFrame();
}

bool TE::Render::WindowLinuxOgl::InitWindow()
{
	m_dpy = XOpenDisplay(NULL);
	if (!m_dpy)
		//Log!!
		return false;

	m_rootWindow = DefaultRootWindow(m_dpy);

	int att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
	m_vi = glXChooseVisual(m_dpy, 0, att);

	if(!m_vi)
		//Log!!
		return false;

	Colormap cmap;
	cmap = XCreateColormap(m_dpy, m_rootWindow, m_vi->visual, AllocNone);

	XSetWindowAttributes swa;
	swa.colormap = cmap;
	swa.event_mask = ExposureMask | KeyPressMask;

	m_window = XCreateWindow(m_dpy, m_rootWindow, GetWindowInfo().posX, GetWindowInfo().posY, GetWindowInfo().width, GetWindowInfo().height, 0, m_vi->depth, InputOutput, m_vi->visual, CWColormap | CWEventMask, &swa);

	XMapWindow(m_dpy, m_window);
	XStoreName(m_dpy, m_window, GetWindowInfo().name.c_str());

	return true;
}

bool TE::Render::WindowLinuxOgl::InitContext()
{
	m_glc = glXCreateContext(m_dpy, m_vi, NULL, GL_TRUE);
	glXMakeCurrent(m_dpy, m_window, m_glc);

	return true;
}

#endif
*/