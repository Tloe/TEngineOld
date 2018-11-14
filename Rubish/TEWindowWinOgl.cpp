/*

#include <TEWindowWinOgl.h>

#if TEWINDOWS

TE::Render::WindowWinOgl::WindowWinOgl( HINSTANCE &hInstance, int nCmdShow, const WindowInf& winInf ) : Window(winInf)
{
	m_nCmdShow = nCmdShow;
	m_hInstance = hInstance;
}

TE::Render::WindowWinOgl::~WindowWinOgl()
{
}

bool TE::Render::WindowWinOgl::Initialize()
{
	return InitWindow() && InitContext();
}

bool TE::Render::WindowWinOgl::DeInitialize()
{
	return	!wglMakeCurrent( NULL, NULL ) || 
		!wglDeleteContext( m_hrc ) ||
		!ReleaseDC( m_hWnd, m_hdc );
}

void TE::Render::WindowWinOgl::NextFrame()
{
	SwapBuffers(m_hdc);
}

bool TE::Render::WindowWinOgl::InitWindow()
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof( WNDCLASSEX );
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
	wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = GetWindowInfo().name.c_str();
	wcex.hIconSm = NULL;

	if(!RegisterClassEx (&wcex))
		//Log
		return false;

	RECT rc =
	{
		GetWindowInfo().posX, GetWindowInfo().posY,
		GetWindowInfo().posX + GetWindowInfo().width,
		GetWindowInfo().posY + GetWindowInfo().height
	};

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	m_hWnd = CreateWindow(
		GetWindowInfo().name.c_str(), GetWindowInfo().name.c_str(),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		rc.right - rc.left, rc.bottom - rc.top,
		NULL, NULL, m_hInstance, NULL );

	if (!m_hWnd)
		//Log
		return false;

	ShowWindow(m_hWnd, m_nCmdShow);

	return true;
}

bool TE::Render::WindowWinOgl::InitContext()
{
	PIXELFORMATDESCRIPTOR pfd;
	int format;

	// get the device context (DC)
	m_hdc = GetDC( m_hWnd );

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

	return true;
}

void TE::Render::WindowWinOgl::TestDrawFunc()
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

LRESULT CALLBACK TE::Render::WindowWinOgl::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch( message )
	{
	case WM_PAINT:
		hdc = BeginPaint( hWnd, &ps );
		EndPaint( hWnd, &ps );
		break;

	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;

	default:
		return DefWindowProc( hWnd, message, wParam, lParam );
	}

	return 0;
}



#endif
*/