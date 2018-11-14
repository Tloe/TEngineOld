#include <TEWindowWin.h>
#include <string>
#include <TEQuitEvent.h>
#include <TEInputEvents.h>
#include <Windowsx.h>

std::map<HWND, TE::Context::WindowWin*> TE::Context::WindowWin::s_allWindows;

TE::Context::WindowWin::WindowWin()
{
}

TE::Context::WindowWin::~WindowWin()
{
}

void TE::Context::WindowWin::Init(Window& window)
{
	m_window = window;

	m_hInstance = (HINSTANCE)GetWindowLong(NULL,GWL_HINSTANCE);

	WNDCLASSEX wcex;

	m_window.SetTitle("TEngine");
	const std::string& title = m_window.GetTitleRef();

	wcex.cbSize = sizeof( WNDCLASSEX );
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
	wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = title.c_str();
	wcex.hIconSm = NULL;

	if(!RegisterClassEx (&wcex))
		//LOG FATAL ERROR
		exit(0);

	int posx = m_window.GetPositionX();
	int posy = m_window.GetPositionY();
	int width = m_window.GetWidth();
	int height = m_window.GetHeight();

	RECT rc =
	{
		posx, posy,
		posx + width,
		posy + height
	};

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	m_hWnd = CreateWindow(
		title.c_str(), title.c_str(),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		rc.right - rc.left, rc.bottom - rc.top,
		NULL, NULL, m_hInstance, NULL );

	if (!m_hWnd)
		//LOG FATAL ERROR
		exit(0);

	AddhWndWinReference(m_hWnd, this);
	ShowWindow(m_hWnd, SW_SHOWNORMAL);
	SetFocus(m_hWnd);
}

void TE::Context::WindowWin::Cleanup()
{
	DestroyWindow(GetHWND());
}

void TE::Context::WindowWin::BeginFrame()
{
	MSG		message;
	while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
	{
		if (message.message == WM_QUIT)
		{
			QuitEvent newEvent;
			newEvent.Invoke();
		}
		else
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}
}

LRESULT CALLBACK TE::Context::WindowWin::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	std::map<HWND,WindowWin*>::iterator itr = s_allWindows.find(hWnd);
	if(itr != s_allWindows.end())
	{
		return (*itr->second).DoWndProc(hWnd, message, wParam, lParam);
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT TE::Context::WindowWin::DoWndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
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
	case WM_KEYDOWN:
		{
			TEInput teInput = m_window.GetInputMapRef().GetTEInputFromVirtualKey(wParam);
			if (teInput != -1)
			{
				int newState;
				m_window.GetPreviousInputState(teInput) == tekInputStateUp ?
					newState = tekInputStateDown : newState = tekInputStateContinued;
				
				m_window.SetPreviousInputState(teInput, newState);
				KeyboardEvent newEvent(newState, teInput);
				newEvent.Invoke();
			}
		}
		break;
	case WM_KEYUP:
		{
			TEInput teInput = m_window.GetInputMapRef().GetTEInputFromVirtualKey(wParam);
			if (teInput != -1)
			{
				m_window.SetPreviousInputState(teInput,tekInputStateUp);
				KeyboardEvent newEvent(tekInputStateUp, teInput);
				newEvent.Invoke();
			}
		}
		break;
	case WM_MOUSEMOVE:
		{
			int xpos = GET_X_LPARAM(lParam);
			int ypos = GET_Y_LPARAM(lParam);
			MouseMoveEvent newEvent(xpos, ypos, m_window.GetPreviousMousePos(0) - xpos, m_window.GetPreviousMousePos(1) - ypos);
			newEvent.Invoke();

			m_window.SetPreviousMousePos(0, xpos);
			m_window.SetPreviousMousePos(1, ypos);

		}
		break;
	case WM_LBUTTONDOWN:
		{
			int newState;
			m_window.GetPreviousInputState(tekInputLMouse) == tekInputStateUp ?
				newState = tekInputStateDown : newState = tekInputStateContinued;

			m_window.SetPreviousInputState(tekInputLMouse, newState);
			
			MouseButtonEvent newEvent(newState, tekInputLMouse);
			newEvent.Invoke();

			SetCapture(m_hWnd);
		}
		break;
	case WM_MBUTTONDOWN:
		{
			int newState;
			m_window.GetPreviousInputState(tekInputMMouse) == tekInputStateUp ?
				newState = tekInputStateDown : newState = tekInputStateContinued;

			m_window.SetPreviousInputState(tekInputMMouse, newState);

			MouseButtonEvent newEvent(newState, tekInputMMouse);
			newEvent.Invoke();

			SetCapture(m_hWnd);
		}
		break;
	case WM_RBUTTONDOWN:
		{
			int newState;
			m_window.GetPreviousInputState(tekInputRMouse) == tekInputStateUp ?
				newState = tekInputStateDown : newState = tekInputStateContinued;

			m_window.SetPreviousInputState(tekInputRMouse, newState);

			MouseButtonEvent newEvent(newState, tekInputRMouse);
			newEvent.Invoke();

			SetCapture(m_hWnd);
		}
		break;
	case WM_LBUTTONUP:
		{
			m_window.SetPreviousInputState(tekInputLMouse, tekInputStateUp);
			MouseButtonEvent newEvent(tekInputStateUp, tekInputLMouse);
			newEvent.Invoke();
			MouseButtonEvent newEvent2(tekInputStateNone, tekInputLClick);
			newEvent2.Invoke();

			ReleaseCapture();
		}
		break;
	case WM_MBUTTONUP:
		{
			m_window.SetPreviousInputState(tekInputMMouse, tekInputStateUp);
			MouseButtonEvent newEvent(tekInputStateUp, tekInputMMouse);
			newEvent.Invoke();
			MouseButtonEvent newEvent2(tekInputStateNone, tekInputMClick);
			newEvent2.Invoke();

			ReleaseCapture();
		}
		break;
	case WM_RBUTTONUP:
		{
			m_window.SetPreviousInputState(tekInputRMouse, tekInputStateUp);
			MouseButtonEvent newEvent(tekInputStateUp, tekInputRMouse);
			newEvent.Invoke();
			MouseButtonEvent newEvent2(tekInputStateNone, tekInputRClick);
			newEvent2.Invoke();		

			ReleaseCapture();
		}
		break;
	case WM_LBUTTONDBLCLK:
		{
			MouseButtonEvent newEvent(tekInputStateNone, tekInputLDoubleClick);
			newEvent.Invoke();
		}
		break;
	case WM_MBUTTONDBLCLK:
		{
			MouseButtonEvent newEvent(tekInputStateNone, tekInputMDoubleClick);
			newEvent.Invoke();
		}
		break;
	case WM_RBUTTONDBLCLK:
		{
			MouseButtonEvent newEvent(tekInputStateNone, tekInputRDoubleClick);
			newEvent.Invoke();
		}
		break;
	case WM_CHAR:
		{
			AsciiInputEvent newEvent(wParam);
			newEvent.Invoke();
		}
		break;
	default:
		return DefWindowProc( hWnd, message, wParam, lParam );
	}

	return 0;
}

void TE::Context::WindowWin::AddhWndWinReference( HWND hWnd, WindowWin* windowRef)
{
	s_allWindows[hWnd] = windowRef;
}

HWND TE::Context::WindowWin::GetHWND()
{
	return m_hWnd;
}

TE::Context::Window& TE::Context::WindowWin::GetWindowRef()
{
	return m_window;
}
