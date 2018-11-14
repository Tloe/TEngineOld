#if defined (_WIN32)

#include "TEWindowMs.h"

TE::Render::WindowMs::WindowMs( HINSTANCE &hInstance, int nCmdShow, const WindowInf& winInf ) : Window(winInf)
{
	//Exception safe constructor
	try
	{
		WNDCLASSEX wcex;

		wcex.cbSize = sizeof( WNDCLASSEX );
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = NULL;
		wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
		wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = WindowInfo().name.c_str();
		wcex.hIconSm = NULL;

		if(!RegisterClassEx (&wcex))
			throw;

		m_hInstance = hInstance;

		RECT rc =
		{
			WindowInfo().posX, WindowInfo().posY,
			WindowInfo().posX + WindowInfo().width,
			WindowInfo().posY + WindowInfo().height
		};

		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

		m_hWnd = CreateWindow(
			WindowInfo().name.c_str(), WindowInfo().name.c_str(),
			WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
			rc.right - rc.left, rc.bottom - rc.top,
			NULL, NULL, m_hInstance, NULL );

		if (!m_hWnd)
			throw;

		ShowWindow(m_hWnd, nCmdShow);
	}
	catch (std::exception& e)
	{

	}
}

#endif
