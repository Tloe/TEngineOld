#include "TEWinWindow.h"
#include "TEInput.h"
#include "TEInputMapper.h"

#include <assert.h>
#include <iostream>

std::unordered_map<HWND, TE::Platform::PlatformWindow *> TE::Platform::PlatformWindow::s_hwndPlatformWindowMap;

TE::Platform::PlatformWindow::PlatformWindow(HWND hwnd,
                                             IO::FileIO &fileIO,
                                             const std::string &windowTitle)
    : m_inputMapper(fileIO),
      m_hWnd(hwnd),
      m_dwWindowStyle(WS_OVERLAPPEDWINDOW),
      m_externalWindow(true),
      m_windowTitle(windowTitle),
      m_width(640),
      m_height(480),
      m_x(-1),
      m_y(-1),
      m_colorBits(32),
      m_fullscreen(false),
      m_setResolutionCalled(false) {
    SetupPlatformInputMap();
}

TE::Platform::PlatformWindow::PlatformWindow(IO::FileIO &fileIO,
                                             const std::string &windowTitle)
    : m_inputMapper(fileIO),
      m_dwWindowStyle(WS_OVERLAPPEDWINDOW),
      m_externalWindow(false),
      m_windowTitle(windowTitle),
      m_width(640),
      m_height(480),
      m_x(-1),
      m_y(-1),
      m_colorBits(32),
      m_fullscreen(false),
      m_setResolutionCalled(false) {
    SetupPlatformInputMap();
}

TE::Platform::PlatformWindow::~PlatformWindow() {
}

void TE::Platform::PlatformWindow::LoadInputFile(const std::string &filePath) {
    m_inputMapper.LoadInputFile(filePath);
}

void TE::Platform::PlatformWindow::SetupPlatformInputMap() {
    m_platformTEInputMap.insert(std::make_pair(0, InputMapping::InputType::Default));
    m_platformTEInputMap.insert(std::make_pair(0, InputMapping::InputType::Key0));
    m_platformTEInputMap.insert(std::make_pair(1, InputMapping::InputType::Key1));
    m_platformTEInputMap.insert(std::make_pair(2, InputMapping::InputType::Key2));
    m_platformTEInputMap.insert(std::make_pair(3, InputMapping::InputType::Key3));
    m_platformTEInputMap.insert(std::make_pair(4, InputMapping::InputType::Key4));
    m_platformTEInputMap.insert(std::make_pair(5, InputMapping::InputType::Key5));
    m_platformTEInputMap.insert(std::make_pair(6, InputMapping::InputType::Key6));
    m_platformTEInputMap.insert(std::make_pair(7, InputMapping::InputType::Key7));
    m_platformTEInputMap.insert(std::make_pair(8, InputMapping::InputType::Key8));
    m_platformTEInputMap.insert(std::make_pair(9, InputMapping::InputType::Key9));
    m_platformTEInputMap.insert(std::make_pair('A', InputMapping::InputType::KeyA));
    m_platformTEInputMap.insert(std::make_pair('B', InputMapping::InputType::KeyB));
    m_platformTEInputMap.insert(std::make_pair('C', InputMapping::InputType::KeyC));
    m_platformTEInputMap.insert(std::make_pair('D', InputMapping::InputType::KeyD));
    m_platformTEInputMap.insert(std::make_pair('E', InputMapping::InputType::KeyE));
    m_platformTEInputMap.insert(std::make_pair('F', InputMapping::InputType::KeyF));
    m_platformTEInputMap.insert(std::make_pair('G', InputMapping::InputType::KeyG));
    m_platformTEInputMap.insert(std::make_pair('H', InputMapping::InputType::KeyH));
    m_platformTEInputMap.insert(std::make_pair('I', InputMapping::InputType::KeyI));
    m_platformTEInputMap.insert(std::make_pair('J', InputMapping::InputType::KeyJ));
    m_platformTEInputMap.insert(std::make_pair('K', InputMapping::InputType::KeyK));
    m_platformTEInputMap.insert(std::make_pair('L', InputMapping::InputType::KeyL));
    m_platformTEInputMap.insert(std::make_pair('M', InputMapping::InputType::KeyM));
    m_platformTEInputMap.insert(std::make_pair('N', InputMapping::InputType::KeyN));
    m_platformTEInputMap.insert(std::make_pair('O', InputMapping::InputType::KeyO));
    m_platformTEInputMap.insert(std::make_pair('P', InputMapping::InputType::KeyP));
    m_platformTEInputMap.insert(std::make_pair('Q', InputMapping::InputType::KeyQ));
    m_platformTEInputMap.insert(std::make_pair('R', InputMapping::InputType::KeyR));
    m_platformTEInputMap.insert(std::make_pair('S', InputMapping::InputType::KeyS));
    m_platformTEInputMap.insert(std::make_pair('T', InputMapping::InputType::KeyT));
    m_platformTEInputMap.insert(std::make_pair('U', InputMapping::InputType::KeyU));
    m_platformTEInputMap.insert(std::make_pair('V', InputMapping::InputType::KeyV));
    m_platformTEInputMap.insert(std::make_pair('W', InputMapping::InputType::KeyW));
    m_platformTEInputMap.insert(std::make_pair('X', InputMapping::InputType::KeyX));
    m_platformTEInputMap.insert(std::make_pair('Y', InputMapping::InputType::KeyY));
    m_platformTEInputMap.insert(std::make_pair('Z', InputMapping::InputType::KeyZ));
    m_platformTEInputMap.insert(std::make_pair(VK_F1, InputMapping::InputType::KeyF1));
    m_platformTEInputMap.insert(std::make_pair(VK_F2, InputMapping::InputType::KeyF2));
    m_platformTEInputMap.insert(std::make_pair(VK_F3, InputMapping::InputType::KeyF3));
    m_platformTEInputMap.insert(std::make_pair(VK_F4, InputMapping::InputType::KeyF4));
    m_platformTEInputMap.insert(std::make_pair(VK_F5, InputMapping::InputType::KeyF5));
    m_platformTEInputMap.insert(std::make_pair(VK_F6, InputMapping::InputType::KeyF6));
    m_platformTEInputMap.insert(std::make_pair(VK_F7, InputMapping::InputType::KeyF7));
    m_platformTEInputMap.insert(std::make_pair(VK_F8, InputMapping::InputType::KeyF8));
    m_platformTEInputMap.insert(std::make_pair(VK_F9, InputMapping::InputType::KeyF9));
    m_platformTEInputMap.insert(std::make_pair(VK_F10, InputMapping::InputType::KeyF10));
    m_platformTEInputMap.insert(std::make_pair(VK_F11, InputMapping::InputType::KeyF11));
    m_platformTEInputMap.insert(std::make_pair(VK_F12, InputMapping::InputType::KeyF12));
    m_platformTEInputMap.insert(std::make_pair(VK_CONTROL, InputMapping::InputType::KeyControlLeft));
    m_platformTEInputMap.insert(std::make_pair(VK_MENU, InputMapping::InputType::KeyAltLeft));
    m_platformTEInputMap.insert(std::make_pair(VK_SHIFT, InputMapping::InputType::KeyShiftLeft));
    m_platformTEInputMap.insert(std::make_pair(VK_SPACE, InputMapping::InputType::KeySpace));
    m_platformTEInputMap.insert(std::make_pair(VK_RETURN, InputMapping::InputType::KeyEnter));
    m_platformTEInputMap.insert(std::make_pair(VK_ESCAPE, InputMapping::InputType::KeyEscape));
    m_platformTEInputMap.insert(std::make_pair(VK_BACK, InputMapping::InputType::KeyBackspace));
    m_platformTEInputMap.insert(std::make_pair(VK_TAB, InputMapping::InputType::KeyTab));
    m_platformTEInputMap.insert(std::make_pair(VK_SEPARATOR, InputMapping::InputType::KeySeperator));
    m_platformTEInputMap.insert(std::make_pair(VK_CAPITAL, InputMapping::InputType::KeyCapslock));
    m_platformTEInputMap.insert(std::make_pair(VK_UP, InputMapping::InputType::KeyUp));
    m_platformTEInputMap.insert(std::make_pair(VK_DOWN, InputMapping::InputType::KeyDown));
    m_platformTEInputMap.insert(std::make_pair(VK_LEFT, InputMapping::InputType::KeyLeft));
    m_platformTEInputMap.insert(std::make_pair(VK_RIGHT, InputMapping::InputType::KeyRight));
    m_platformTEInputMap.insert(std::make_pair(VK_PRIOR, InputMapping::InputType::KeyPgUp));
    m_platformTEInputMap.insert(std::make_pair(VK_NEXT, InputMapping::InputType::KeyPgDown));
    m_platformTEInputMap.insert(std::make_pair(VK_HOME, InputMapping::InputType::KeyHome));
    m_platformTEInputMap.insert(std::make_pair(VK_END, InputMapping::InputType::KeyEnd));
    m_platformTEInputMap.insert(std::make_pair(VK_NUMPAD0, InputMapping::InputType::KeyNum0));
    m_platformTEInputMap.insert(std::make_pair(VK_NUMPAD1, InputMapping::InputType::KeyNum1));
    m_platformTEInputMap.insert(std::make_pair(VK_NUMPAD2, InputMapping::InputType::KeyNum2));
    m_platformTEInputMap.insert(std::make_pair(VK_NUMPAD3, InputMapping::InputType::KeyNum3));
    m_platformTEInputMap.insert(std::make_pair(VK_NUMPAD4, InputMapping::InputType::KeyNum4));
    m_platformTEInputMap.insert(std::make_pair(VK_NUMPAD5, InputMapping::InputType::KeyNum5));
    m_platformTEInputMap.insert(std::make_pair(VK_NUMPAD6, InputMapping::InputType::KeyNum6));
    m_platformTEInputMap.insert(std::make_pair(VK_NUMPAD7, InputMapping::InputType::KeyNum7));
    m_platformTEInputMap.insert(std::make_pair(VK_NUMPAD8, InputMapping::InputType::KeyNum8));
    m_platformTEInputMap.insert(std::make_pair(VK_NUMPAD9, InputMapping::InputType::KeyNum9));
    m_platformTEInputMap.insert(std::make_pair(VK_OEM_1, InputMapping::InputType::KeyCollon));
    m_platformTEInputMap.insert(std::make_pair(VK_OEM_PLUS, InputMapping::InputType::KeyPlus));
    m_platformTEInputMap.insert(std::make_pair(VK_OEM_COMMA, InputMapping::InputType::KeyComma));
    m_platformTEInputMap.insert(std::make_pair(VK_OEM_MINUS, InputMapping::InputType::KeyMinus));
    m_platformTEInputMap.insert(std::make_pair(VK_OEM_PERIOD, InputMapping::InputType::KeyPeriod));
    m_platformTEInputMap.insert(std::make_pair(VK_OEM_2, InputMapping::InputType::KeySlashQuest));
    m_platformTEInputMap.insert(std::make_pair(VK_OEM_3, InputMapping::InputType::KeyTilde));
    m_platformTEInputMap.insert(std::make_pair(VK_LBUTTON, InputMapping::InputType::MouseLButton));
    m_platformTEInputMap.insert(std::make_pair(VK_MBUTTON, InputMapping::InputType::MouseRButton));
    m_platformTEInputMap.insert(std::make_pair(VK_RBUTTON, InputMapping::InputType::MouseRButton));
}

void TE::Platform::PlatformWindow::Initialize() {
    if (!m_externalWindow) {
        m_hInstance        = (HINSTANCE)GetWindowLongPtr(NULL, GWLP_HINSTANCE);

        WNDCLASSEX wcex    = {};

        wcex.cbSize        = sizeof(WNDCLASSEX);
        wcex.style         = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
        wcex.lpfnWndProc   = WndProc;
        wcex.cbClsExtra    = 0;
        wcex.cbWndExtra    = 0;
        wcex.hInstance     = m_hInstance;
        wcex.hIcon         = NULL;
        wcex.hCursor       = LoadCursor(NULL, IDC_ARROW);
        wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wcex.lpszMenuName  = NULL;
        wcex.lpszClassName = m_windowTitle.c_str();
        wcex.hIconSm       = NULL;

        if (!RegisterClassEx(&wcex))
            // LOG FATAL ERROR
            exit(0);

        I32 posx   = 0;
        I32 posy   = 0;
        I32 width  = m_width;
        I32 height = m_height;

        RECT rc =
            {
                posx, posy,
                posx + width,
                posy + height};

        AdjustWindowRect(&rc, m_dwWindowStyle, false);

        m_hWnd = CreateWindow(
            m_windowTitle.c_str(),
            m_windowTitle.c_str(),
            m_dwWindowStyle | WS_CAPTION | WS_SYSMENU, //| WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
            // WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT,
            rc.right - rc.left, rc.bottom - rc.top,
            NULL, NULL, m_hInstance, NULL);

        if (!m_hWnd)
            // LOG FATAL ERROR
            exit(0);

        s_hwndPlatformWindowMap.insert(std::make_pair(m_hWnd, this));
        ShowWindow(m_hWnd, SW_SHOWNORMAL);
        SetFocus(m_hWnd);
    }

    m_hdc = GetDC(m_hWnd);

    OnOpenWindow();
}

TE::InputMapping::InputMapper &TE::Platform::PlatformWindow::GetInputMapper() {
    return m_inputMapper;
}

void TE::Platform::PlatformWindow::Cleanup() {
    OnCloseWindow();

    if (m_hWnd && m_hdc) {
        ReleaseDC(m_hWnd, m_hdc);
    }

    DestroyWindow(m_hWnd);
}

void TE::Platform::PlatformWindow::SetResolution(bool fullscreen, I32 width, I32 height, I32 colorBits, I32 positionX, I32 positionY) {
    m_width     = width;
    m_height    = height;
    m_colorBits = colorBits;

    if (!m_externalWindow) {
        if (fullscreen) {
            // SetWindowLongPtr(m_hWnd, GWL_STYLE, WS_OVERLAPPED | WS_VISIBLE);
            if (!m_fullscreen)
                SwitchToFullscreen();
            MoveWindow(m_hWnd, 0, 0, m_width, m_height, false);
        } else {
            if (positionX == -1 || positionY == -1) {
                m_x = (GetScreenWidth() - m_width) / 2;
                m_y = (GetScreenHeight() - m_height) / 2;
            } else {
                m_x = positionX;
                m_y = positionY;
            }

            RECT rc =
                {
                    m_x, m_y,
                    m_x + m_width,
                    m_y + m_height};

            AdjustWindowRect(&rc, m_dwWindowStyle, false);

            if (m_fullscreen)
                SwitchToWindowed();
            MoveWindow(m_hWnd, m_x, m_y, rc.right - rc.left, rc.bottom - rc.top, false);
        }
    }

    m_setResolutionCalled = true;
}

void TE::Platform::PlatformWindow::SwitchToFullscreen() {
    DEVMODE dmScreenSettings;
    memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
    dmScreenSettings.dmSize       = sizeof(dmScreenSettings);
    dmScreenSettings.dmPelsWidth  = m_width;
    dmScreenSettings.dmPelsHeight = m_height;
    dmScreenSettings.dmBitsPerPel = m_colorBits;
    // dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;
    dmScreenSettings.dmFields     = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL | DM_DISPLAYFREQUENCY;

    if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) == DISP_CHANGE_SUCCESSFUL) {
        SetWindowLong(m_hWnd, GWL_STYLE, WS_POPUP);

        // ShowCursor(FALSE);
        ShowWindow(m_hWnd, SW_SHOW);
        SetForegroundWindow(m_hWnd);
        m_fullscreen = true;
    }
}

void TE::Platform::PlatformWindow::SwitchToWindowed() {
    SetWindowLong(m_hWnd, GWL_STYLE, m_dwWindowStyle | WS_CAPTION | WS_SYSMENU);
    ChangeDisplaySettings(NULL, 0);
    // ShowCursor(TRUE);
    ShowWindow(m_hWnd, SW_SHOW);
    SetForegroundWindow(m_hWnd);
    m_fullscreen = false;
}

I32 TE::Platform::PlatformWindow::GetWindowWidth() {
    return m_width;
}

I32 TE::Platform::PlatformWindow::GetWindowHeight() {
    return m_height;
}

I32 TE::Platform::PlatformWindow::GetScreenWidth() {
    return GetSystemMetrics(SM_CXSCREEN);
}

I32 TE::Platform::PlatformWindow::GetScreenHeight() {
    return GetSystemMetrics(SM_CYSCREEN);
}

bool TE::Platform::PlatformWindow::MessageLoop() {
    bool quitMessageReceived = false;

    m_asciiInput.clear();

    MSG message;
    while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
        if (message.message == WM_QUIT) {
            // PostQuitMessage(0);
            quitMessageReceived = true;
        } else {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
    }

    m_inputMapper.Dispatch();

    return quitMessageReceived;
}

HWND TE::Platform::PlatformWindow::GetHWND() {
    return m_hWnd;
}

LRESULT CALLBACK TE::Platform::PlatformWindow::WndProc(HWND hWnd, U32 message, WPARAM wParam, LPARAM lParam) {
    std::unordered_map<HWND, PlatformWindow *>::iterator itr = s_hwndPlatformWindowMap.find(hWnd);
    if (itr != s_hwndPlatformWindowMap.end()) {
        return (*itr->second).DoWndProc(hWnd, message, wParam, lParam);
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT TE::Platform::PlatformWindow::DoWndProc(HWND hWnd, U32 message, WPARAM wParam, LPARAM lParam) {
    static I64 previouseMousePos[] = {0, 0};

    PAINTSTRUCT ps;
    HDC hdc;

    switch (message) {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        // PostQuitMessage( WM_QUIT );
        m_quitMessageReceived = true;
        break;
    case WM_SIZE: {
        I32 width  = LOWORD(lParam);
        I32 height = HIWORD(lParam);

        if (!m_setResolutionCalled) {
            SetResolution(m_fullscreen, width, height, m_colorBits, m_x, m_y);
        }
    } break;
    case WM_CHAR: {
        char ascii = static_cast<char>(wParam);

        m_asciiInput.push_back(ascii);
    } break;
    case WM_MOUSEMOVE: {
        I64 x                = LOWORD(lParam);
        I64 y                = HIWORD(lParam);

        F64 normalizedX      = static_cast<F64>(x) / m_width;
        F64 normalizedY      = static_cast<F64>(y) / m_height;

        F64 normalizedDeltaX = static_cast<F64>(previouseMousePos[0] - x) / m_width;
        F64 normalizedDeltaY = static_cast<F64>(previouseMousePos[1] - y) / m_height;

        assert(normalizedDeltaX > -1.0 && normalizedDeltaX < 1.0 && "Oops, looks like this needs some debugging");
        assert(normalizedDeltaY > -1.0 && normalizedDeltaY < 1.0 && "Oops, looks like this needs some debugging");

        m_inputMapper.MapRangeInput(InputMapping::RangeInput::MouseX, normalizedX);
        m_inputMapper.MapRangeInput(InputMapping::RangeInput::MouseY, normalizedY);
        m_inputMapper.MapRangeInput(InputMapping::RangeInput::MouseDeltaX, normalizedDeltaX);
        m_inputMapper.MapRangeInput(InputMapping::RangeInput::MouseDeltaY, normalizedDeltaY);

        previouseMousePos[0] = x;
        previouseMousePos[1] = y;
    } break;
    case WM_KEYDOWN: {
        PlatformEngineInputMap::iterator findItr = m_platformTEInputMap.find(wParam);
        if (findItr != m_platformTEInputMap.end()) {
            bool previouslyPressed = ((lParam & static_cast<U32>(1) << 31) != 0);
            bool pressed           = true;
            m_inputMapper.MapInput(findItr->second, pressed, previouslyPressed);
        }
    } break;
    case WM_KEYUP: {
        PlatformEngineInputMap::iterator findItr = m_platformTEInputMap.find(wParam);
        if (findItr != m_platformTEInputMap.end()) {
            bool previouslyPressed = ((lParam & (static_cast<U32>(1) << 31)) != 0);
            bool pressed           = false;
            m_inputMapper.MapInput(findItr->second, pressed, previouslyPressed);
        }
    } break;
    /*case WM_LBUTTONDOWN:
      {
        HandleDownState(InputMapping::InputType::MouseLButton);
        SetCapture(hWnd);
      }
      break;
    case WM_MBUTTONDOWN:
      {
        HandleDownState(InputMapping::InputType::MouseMButton);
        SetCapture(hWnd);
      }
      break;
    case WM_RBUTTONDOWN:
      {
        HandleDownState(InputMapping::InputType::MouseRButton);
        SetCapture(hWnd);
      }
      break;*/
    /*case WM_LBUTTONUP:
      {
        HandleUpState(InputMapping::InputType::MouseLButton);

        m_platformInputQue.push(PlatformInput(InputMapping::InputType::MouseLClick));

        ReleaseCapture();
      }
      break;
    case WM_MBUTTONUP:
      {
        HandleUpState(InputMapping::InputType::MouseMButton);

        m_platformInputQue.push(PlatformInput(InputMapping::InputType::MouseMClick));

        ReleaseCapture();
      }
      break;
    case WM_RBUTTONUP:
      {
        HandleUpState(InputMapping::InputType::MouseRButton);

        m_platformInputQue.push(PlatformInput(InputMapping::InputType::MouseRClick));

        ReleaseCapture();
      }
      break;
    case WM_LBUTTONDBLCLK:
      {
        m_platformInputQue.push(PlatformInput(InputMapping::InputType::MouseLDoubleClick));
      }
      break;
    case WM_MBUTTONDBLCLK:
      {
        m_platformInputQue.push(PlatformInput(InputMapping::InputType::MouseMDoubleClick));
      }
      break;
    case WM_RBUTTONDBLCLK:
      {
        m_platformInputQue.push(PlatformInput(InputMapping::InputType::MouseRDoubleClick));
      }
      break;*/
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

/*void TE::Platform::PlatformWindow::HandleDownState( Enum input )
{
  Enum newState;
  m_previouseInput[input];
  if(m_previouseInput[input] == InputState::Up)
  {
    newState = InputState::Down;
  }
  else
  {
    newState = InputState::Continued;
  }

  m_platformInputQue.push(PlatformInput(input, newState));

  m_previouseInput[input] = newState;
}

void TE::Platform::PlatformWindow::HandleUpState( Enum input )
{
  m_platformInputQue.push(PlatformInput(input, InputState::Up));

  m_previouseInput[input] = InputState::Up;
}

bool TE::Platform::PlatformWindow::IsFullscreen()
{
  return m_fullscreen;
}

bool TE::Platform::PlatformWindow::PullNextPlatformInput( PlatformInput& inputOut )
{
  if (m_platformInputQue.size() > 0)
  {
    inputOut = m_platformInputQue.front();
    m_platformInputQue.pop();

    return true;
  }

  return false;
}

bool TE::Platform::PlatformWindow::PullNextPlatformMousePos( PlatformMousePos& mousePosOut )
{
  if (m_platformMousePosQue.size() > 0)
  {
    mousePosOut = m_platformMousePosQue.front();
    m_platformMousePosQue.pop();

    return true;
  }

  return false;
}
*/

std::vector<char> TE::Platform::PlatformWindow::GetAsciiInput() {
    return m_asciiInput;
}

void TE::Platform::PlatformWindow::SetWindowTitle(const std::string &title) {
    m_windowTitle = title;
    SetWindowText(m_hWnd, m_windowTitle.c_str());
}
