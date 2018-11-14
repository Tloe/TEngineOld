#include <TEPlatformContextWin.h>
#include <TEQuitEvent.h>
#include <TESystemEvents.h>
#include "TETimedEvent.h"

std::map<HWND, TE::Context::PlatformContext*> TE::Context::PlatformContext::s_allWindows;

TE::Context::PlatformContext::PlatformContext( HWND hwnd )
	:
	m_hWnd(hwnd),
	m_externalWindow(true),
	m_width(640),
	m_height(480),
	m_colorBits(32),
	m_fullscreen(false),
	m_dwWindowStyle(WS_OVERLAPPEDWINDOW)
{

}

TE::Context::PlatformContext::PlatformContext()
	:
	m_externalWindow(false),
	m_width(640),
	m_height(480),
	m_colorBits(32),
	m_fullscreen(false),
	m_dwWindowStyle(WS_OVERLAPPEDWINDOW)
{

}

void TE::Context::PlatformContext::Init()
{
	if (!m_externalWindow)
	{
		m_hInstance = (HINSTANCE)GetWindowLong(NULL,GWL_HINSTANCE);

		WNDCLASSEX wcex;

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
		wcex.lpszClassName = "TEngine";
		wcex.hIconSm = NULL;

		if(!RegisterClassEx (&wcex))
			//LOG FATAL ERROR
			exit(0);

		I32 posx = 0;
		I32 posy = 0;
		I32 width = m_width;
		I32 height = m_height;

		RECT rc =
		{
			posx, posy,
			posx + width,
			posy + height
		};

		AdjustWindowRect(&rc, m_dwWindowStyle, false);

		m_hWnd = CreateWindow(
			"TEngine", "TEngine",
			m_dwWindowStyle | WS_CAPTION | WS_SYSMENU, //| WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
			//WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			rc.right - rc.left, rc.bottom - rc.top,
			NULL, NULL, m_hInstance, NULL );

		if (!m_hWnd)
			//LOG FATAL ERROR
			exit(0);

		AddhWndWinReference(m_hWnd, this);
		ShowWindow(m_hWnd, SW_SHOWNORMAL);
		SetFocus(m_hWnd);
	}

	m_hdc = GetDC(m_hWnd);
}

void TE::Context::PlatformContext::SetResolution(bool fullscreen, I32 width /*= 640*/, I32 height /*= 480*/, I32 colorBits /*= 32*/ )
{
	m_width = width;
	m_height = height;
	m_colorBits = colorBits;
	
	if(!m_externalWindow)
	{
		if (fullscreen)
		{
			//SetWindowLongPtr(m_hWnd, GWL_STYLE, WS_OVERLAPPED | WS_VISIBLE);
			if (!m_fullscreen) SwitchToFullscreen();
			MoveWindow(m_hWnd, 0, 0, width, height, false);
		}
		else
		{
			I32 x = (GetScreenWidth() - width) / 2;
			I32 y = (GetScreenHeight() - height) / 2;

			RECT rc =
			{
				x, y,
				x + width,
				y + height
			};

			AdjustWindowRect(&rc, m_dwWindowStyle, false);

			//I32 heightDelta = GetSystemMetrics(SM_CYSIZEFRAME)  + GetSystemMetrics(SM_CYCAPTION) - (GetSystemMetrics(SM_CYBORDER)*2);
			//I32 widthDelta = GetSystemMetrics(SM_CXSIZEFRAME) - (GetSystemMetrics(SM_CXBORDER)*2);
			
			//SetWindowLongPtr(m_hWnd, GWL_STYLE, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_VISIBLE);
			if(m_fullscreen) SwitchToWindowed();
			MoveWindow(m_hWnd, x, y, rc.right - rc.left, rc.bottom - rc.top, false);
		}
	}
}

void TE::Context::PlatformContext::SwitchToFullscreen()
{
	DEVMODE dmScreenSettings; 
	memset(&dmScreenSettings,0,sizeof(dmScreenSettings)); 
	dmScreenSettings.dmSize =sizeof(dmScreenSettings); 
	dmScreenSettings.dmPelsWidth = m_width; 
	dmScreenSettings.dmPelsHeight = m_height; 
	dmScreenSettings.dmBitsPerPel = m_colorBits; 
	//dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;
	dmScreenSettings.dmFields= DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL | DM_DISPLAYFREQUENCY;

	if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)	== DISP_CHANGE_SUCCESSFUL)
	{
		SetWindowLong(m_hWnd,GWL_STYLE, WS_POPUP );

		//ShowCursor(FALSE);
		ShowWindow(m_hWnd,SW_SHOW);
		SetForegroundWindow(m_hWnd);
		m_fullscreen = true;
	}
}

void TE::Context::PlatformContext::SwitchToWindowed()
{
	SetWindowLong(m_hWnd, GWL_STYLE, m_dwWindowStyle | WS_CAPTION | WS_SYSMENU );
	ChangeDisplaySettings(NULL,0); 
	//ShowCursor(TRUE);
	ShowWindow(m_hWnd,SW_SHOW);
	SetForegroundWindow(m_hWnd);
	m_fullscreen = false;
}

I32 TE::Context::PlatformContext::GetWindowWidth()
{
	return m_width;
}

I32 TE::Context::PlatformContext::GetWindowHeight()
{
	return m_height;
}

I32 TE::Context::PlatformContext::GetScreenWidth()
{
	return GetSystemMetrics(SM_CXSCREEN);
}

I32 TE::Context::PlatformContext::GetScreenHeight()
{
	return GetSystemMetrics(SM_CYSCREEN);
}

void TE::Context::PlatformContext::Cleanup()
{
	if ( m_hWnd && m_hdc )
	{
		ReleaseDC( m_hWnd, m_hdc );
	}

	DestroyWindow(m_hWnd);
}

void TE::Context::PlatformContext::BeginFrame()
{
	MSG		message;
	while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
	{
		if (message.message == WM_QUIT)
		{
			TE::Context::QuitEvent newEvent;
			newEvent.Invoke();
		}
		else
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}
}

void TE::Context::PlatformContext::EndFrame()
{
	
}

HWND TE::Context::PlatformContext::GetHWND()
{
	return m_hWnd;
}

LRESULT CALLBACK TE::Context::PlatformContext::WndProc( HWND hWnd, U32 message, WPARAM wParam, LPARAM lParam )
{
	std::map<HWND,PlatformContext*>::iterator itr = s_allWindows.find(hWnd);
	if(itr != s_allWindows.end())
	{
		return (*itr->second).DoWndProc(hWnd, message, wParam, lParam);
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT TE::Context::PlatformContext::DoWndProc( HWND hWnd, U32 message, WPARAM wParam, LPARAM lParam )
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
			TEInput teInput = m_platformTEInputMap[wParam];
			if (teInput != -1)
			{
				TEInputState newState;
				if(m_previouseInputState[teInput] == tekInputStateUp)
				{
					newState = tekInputStateDown;
				}
				else
				{
					newState = tekInputStateContinued;
				}

				m_previouseInputState[teInput] = newState;
				KeyboardEvent newEvent(newState, teInput);
				newEvent.Invoke();
			}
		}
		break;
	case WM_KEYUP:
		{
			TEInput teInput = m_platformTEInputMap[wParam];
			if (teInput != -1)
			{
				m_previouseInputState[teInput] = tekInputStateUp;
				KeyboardEvent newEvent(tekInputStateUp, teInput);
				newEvent.Invoke();
			}
		}
		break;
	case WM_MOUSEMOVE:
		{
			//I32 xpos = GET_X_LPARAM(lParam);
			I32 xpos = LOWORD(lParam);
			//I32 ypos = GET_Y_LPARAM(lParam);
			I32 ypos = HIWORD(lParam);
			MouseMoveEvent newEvent(xpos, ypos, m_previouseMousePos[0] - xpos, m_previouseMousePos[1] - ypos);
			newEvent.Invoke();

			m_previouseMousePos[0] = xpos;
			m_previouseMousePos[1] = ypos;
		}
		break;
	case WM_LBUTTONDOWN:
		{
			TEInputState newState;
			if(m_previouseInputState[tekInputLMouse] == tekInputStateUp)
			{
				newState = tekInputStateDown;
			}
			else
			{
				newState = tekInputStateContinued;
			}

			m_previouseInputState[tekInputLMouse] = newState;
			MouseButtonEvent newEvent(newState, tekInputLMouse);
			newEvent.Invoke();

			SetCapture(m_hWnd);
		}
		break;
	case WM_MBUTTONDOWN:
		{
			TEInputState newState;
			if(m_previouseInputState[tekInputMMouse] == tekInputStateUp)
			{
				newState = tekInputStateDown;
			}
			else
			{
				newState = tekInputStateContinued;
			}

			m_previouseInputState[tekInputMMouse] = newState;

			MouseButtonEvent newEvent(newState, tekInputMMouse);
			newEvent.Invoke();

			SetCapture(m_hWnd);
		}
		break;
	case WM_RBUTTONDOWN:
		{
			TEInputState newState;
			if(m_previouseInputState[tekInputRMouse] == tekInputStateUp)
			{
				newState = tekInputStateDown;
			}
			else
			{
				newState = tekInputStateContinued;
			}

			m_previouseInputState[tekInputRMouse] = newState;

			MouseButtonEvent newEvent(newState, tekInputRMouse);
			newEvent.Invoke();

			SetCapture(m_hWnd);
		}
		break;
	case WM_LBUTTONUP:
		{
			m_previouseInputState[tekInputLMouse] = tekInputStateUp;
			
			MouseButtonEvent newEvent(tekInputStateUp, tekInputLMouse);
			newEvent.Invoke();
			
			MouseButtonEvent newEvent2(tekInputStateNone, tekInputLClick);
			newEvent2.Invoke();

			ReleaseCapture();
		}
		break;
	case WM_MBUTTONUP:
		{
			m_previouseInputState[tekInputMMouse] = tekInputStateUp;

			MouseButtonEvent newEvent(tekInputStateUp, tekInputMMouse);
			newEvent.Invoke();
			MouseButtonEvent newEvent2(tekInputStateNone, tekInputMClick);
			newEvent2.Invoke();

			ReleaseCapture();
		}
		break;
	case WM_RBUTTONUP:
		{
			m_previouseInputState[tekInputRMouse] = tekInputStateUp;

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
	case WM_SIZE:
		{
			I32 width = LOWORD(lParam);
			I32 height = HIWORD(lParam);
			WindowResizeEvent newEvent(width, height);
			newEvent.Invoke();
		}
	default:
		return DefWindowProc( hWnd, message, wParam, lParam );
	}

	return 0;
}

void TE::Context::PlatformContext::AddhWndWinReference( HWND hWnd, PlatformContext* contextRef )
{
	s_allWindows.insert(std::make_pair(hWnd, contextRef));
}

void TE::Context::PlatformContext::InitInputMap()
{
	m_platformTEInputMap.insert(std::make_pair(0,tekInputKey0));
	m_platformTEInputMap.insert(std::make_pair(1,tekInputKey1));
	m_platformTEInputMap.insert(std::make_pair(2,tekInputKey2));
	m_platformTEInputMap.insert(std::make_pair(3,tekInputKey3));
	m_platformTEInputMap.insert(std::make_pair(4,tekInputKey4));
	m_platformTEInputMap.insert(std::make_pair(5,tekInputKey5));
	m_platformTEInputMap.insert(std::make_pair(6,tekInputKey6));
	m_platformTEInputMap.insert(std::make_pair(7,tekInputKey7));
	m_platformTEInputMap.insert(std::make_pair(8,tekInputKey8));
	m_platformTEInputMap.insert(std::make_pair(9,tekInputKey9));
	m_platformTEInputMap.insert(std::make_pair('A',tekInputKeyA));
	m_platformTEInputMap.insert(std::make_pair('B',tekInputKeyB));
	m_platformTEInputMap.insert(std::make_pair('C',tekInputKeyC));
	m_platformTEInputMap.insert(std::make_pair('D',tekInputKeyD));
	m_platformTEInputMap.insert(std::make_pair('E',tekInputKeyE));
	m_platformTEInputMap.insert(std::make_pair('F',tekInputKeyF));
	m_platformTEInputMap.insert(std::make_pair('G',tekInputKeyG));
	m_platformTEInputMap.insert(std::make_pair('H',tekInputKeyH));
	m_platformTEInputMap.insert(std::make_pair('I',tekInputKeyI));
	m_platformTEInputMap.insert(std::make_pair('J',tekInputKeyJ));
	m_platformTEInputMap.insert(std::make_pair('K',tekInputKeyK));
	m_platformTEInputMap.insert(std::make_pair('L',tekInputKeyL));
	m_platformTEInputMap.insert(std::make_pair('M',tekInputKeyM));
	m_platformTEInputMap.insert(std::make_pair('N',tekInputKeyN));
	m_platformTEInputMap.insert(std::make_pair('O',tekInputKeyO));
	m_platformTEInputMap.insert(std::make_pair('P',tekInputKeyP));
	m_platformTEInputMap.insert(std::make_pair('Q',tekInputKeyQ));
	m_platformTEInputMap.insert(std::make_pair('R',tekInputKeyR));
	m_platformTEInputMap.insert(std::make_pair('S',tekInputKeyS));
	m_platformTEInputMap.insert(std::make_pair('T',tekInputKeyT));
	m_platformTEInputMap.insert(std::make_pair('U',tekInputKeyU));
	m_platformTEInputMap.insert(std::make_pair('V',tekInputKeyV));
	m_platformTEInputMap.insert(std::make_pair('W',tekInputKeyW));
	m_platformTEInputMap.insert(std::make_pair('X',tekInputKeyX));
	m_platformTEInputMap.insert(std::make_pair('Y',tekInputKeyY));
	m_platformTEInputMap.insert(std::make_pair('Z',tekInputKeyZ));
	m_platformTEInputMap.insert(std::make_pair(VK_F1,tekInputKeyF1));
	m_platformTEInputMap.insert(std::make_pair(VK_F2,tekInputKeyF2));
	m_platformTEInputMap.insert(std::make_pair(VK_F3,tekInputKeyF3));
	m_platformTEInputMap.insert(std::make_pair(VK_F4,tekInputKeyF4));
	m_platformTEInputMap.insert(std::make_pair(VK_F5,tekInputKeyF5));
	m_platformTEInputMap.insert(std::make_pair(VK_F6,tekInputKeyF6));
	m_platformTEInputMap.insert(std::make_pair(VK_F7,tekInputKeyF7));
	m_platformTEInputMap.insert(std::make_pair(VK_F8,tekInputKeyF8));
	m_platformTEInputMap.insert(std::make_pair(VK_F9,tekInputKeyF9));
	m_platformTEInputMap.insert(std::make_pair(VK_F10,tekInputKeyF10));
	m_platformTEInputMap.insert(std::make_pair(VK_F11,tekInputKeyF11));
	m_platformTEInputMap.insert(std::make_pair(VK_F12,tekInputKeyF12));
	m_platformTEInputMap.insert(std::make_pair(VK_CONTROL,tekInputKeyControlLeft));
	m_platformTEInputMap.insert(std::make_pair(VK_MENU,tekInputKeyAltLeft));
	m_platformTEInputMap.insert(std::make_pair(VK_SHIFT,tekInputKeyShiftLeft));
	m_platformTEInputMap.insert(std::make_pair(VK_SPACE,tekInputKeySpace));
	m_platformTEInputMap.insert(std::make_pair(VK_RETURN,tekInputKeyEnter));
	m_platformTEInputMap.insert(std::make_pair(VK_ESCAPE,tekInputKeyEscape));
	m_platformTEInputMap.insert(std::make_pair(VK_BACK,tekInputKeyBackspace));
	m_platformTEInputMap.insert(std::make_pair(VK_TAB,tekInputKeyTab));
	m_platformTEInputMap.insert(std::make_pair(VK_SEPARATOR,tekInputKeySeperator));
	m_platformTEInputMap.insert(std::make_pair(VK_CAPITAL,tekInputKeyCapslock));
	m_platformTEInputMap.insert(std::make_pair(VK_UP,tekInputKeyUp));
	m_platformTEInputMap.insert(std::make_pair(VK_DOWN,tekInputKeyDown));
	m_platformTEInputMap.insert(std::make_pair(VK_LEFT,tekInputKeyLeft));
	m_platformTEInputMap.insert(std::make_pair(VK_RIGHT,tekInputKeyRight));
	m_platformTEInputMap.insert(std::make_pair(VK_PRIOR,tekInputKeyPgUp));
	m_platformTEInputMap.insert(std::make_pair(VK_NEXT,tekInputKeyPgDown));
	m_platformTEInputMap.insert(std::make_pair(VK_HOME,tekInputKeyHome));
	m_platformTEInputMap.insert(std::make_pair(VK_END,tekInputKeyEnd));
	m_platformTEInputMap.insert(std::make_pair(VK_NUMPAD0,tekInputKeyNum0));
	m_platformTEInputMap.insert(std::make_pair(VK_NUMPAD1,tekInputKeyNum1));
	m_platformTEInputMap.insert(std::make_pair(VK_NUMPAD2,tekInputKeyNum2));
	m_platformTEInputMap.insert(std::make_pair(VK_NUMPAD3,tekInputKeyNum3));
	m_platformTEInputMap.insert(std::make_pair(VK_NUMPAD4,tekInputKeyNum4));
	m_platformTEInputMap.insert(std::make_pair(VK_NUMPAD5,tekInputKeyNum5));
	m_platformTEInputMap.insert(std::make_pair(VK_NUMPAD6,tekInputKeyNum6));
	m_platformTEInputMap.insert(std::make_pair(VK_NUMPAD7,tekInputKeyNum7));
	m_platformTEInputMap.insert(std::make_pair(VK_NUMPAD8,tekInputKeyNum8));
	m_platformTEInputMap.insert(std::make_pair(VK_NUMPAD9,tekInputKeyNum9));
	m_platformTEInputMap.insert(std::make_pair(VK_OEM_1,tekInputKeyCollon));
	m_platformTEInputMap.insert(std::make_pair(VK_OEM_PLUS,tekInputKeyPlus));
	m_platformTEInputMap.insert(std::make_pair(VK_OEM_COMMA,tekInputKeyComma));
	m_platformTEInputMap.insert(std::make_pair(VK_OEM_MINUS,tekInputKeyMinus));
	m_platformTEInputMap.insert(std::make_pair(VK_OEM_PERIOD,tekInputKeyPeriod));
	m_platformTEInputMap.insert(std::make_pair(VK_OEM_2,tekInputKeySlashQuest));
	m_platformTEInputMap.insert(std::make_pair(VK_OEM_3,tekInputKeyTilde));
	m_platformTEInputMap.insert(std::make_pair(VK_LBUTTON,tekInputLMouse));
	m_platformTEInputMap.insert(std::make_pair(VK_MBUTTON,tekInputMMouse));
	m_platformTEInputMap.insert(std::make_pair(VK_RBUTTON,tekInputRMouse));
}
