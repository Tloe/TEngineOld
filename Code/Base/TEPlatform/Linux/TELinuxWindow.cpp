#include "TELinuxWindow.h"
#include "TEInput.h"
#include "TEInputMapper.h"

#include <assert.h>
#include <iostream>
#include <X11/keysymdef.h>

namespace
{
    int XErrorHandlerFunction(Display *dsp, XErrorEvent *error)
    {
      char errorstring[128];
      XGetErrorText(dsp, error->error_code, errorstring, 128);

      //LOG FATAL
      std::cout << "ack!fatal: X error--" << errorstring << std::endl;
      exit(-1);
    }

    struct Hints
    {
        U64 flags;
        U64 functions;
        U64 decorations;
        I64 inputMode;
        U64 status;
    };

    void SetupMapping(std::unordered_map<I32, Enum> & map)
    {
        map.insert(std::make_pair(XK_0, TE::InputMapping::InputType::Key0));
        map.insert(std::make_pair(XK_1, TE::InputMapping::InputType::Key1));
        map.insert(std::make_pair(XK_2, TE::InputMapping::InputType::Key2));
        map.insert(std::make_pair(XK_3, TE::InputMapping::InputType::Key3));
        map.insert(std::make_pair(XK_4, TE::InputMapping::InputType::Key4));
        map.insert(std::make_pair(XK_5, TE::InputMapping::InputType::Key5));
        map.insert(std::make_pair(XK_6, TE::InputMapping::InputType::Key6));
        map.insert(std::make_pair(XK_7, TE::InputMapping::InputType::Key7));
        map.insert(std::make_pair(XK_8, TE::InputMapping::InputType::Key8));
        map.insert(std::make_pair(XK_9, TE::InputMapping::InputType::Key9));
        map.insert(std::make_pair(XK_a, TE::InputMapping::InputType::KeyA));
        map.insert(std::make_pair(XK_b, TE::InputMapping::InputType::KeyB));
        map.insert(std::make_pair(XK_c, TE::InputMapping::InputType::KeyC));
        map.insert(std::make_pair(XK_d, TE::InputMapping::InputType::KeyD));
        map.insert(std::make_pair(XK_e, TE::InputMapping::InputType::KeyE));
        map.insert(std::make_pair(XK_f, TE::InputMapping::InputType::KeyF));
        map.insert(std::make_pair(XK_g, TE::InputMapping::InputType::KeyG));
        map.insert(std::make_pair(XK_h, TE::InputMapping::InputType::KeyH));
        map.insert(std::make_pair(XK_i, TE::InputMapping::InputType::KeyI));
        map.insert(std::make_pair(XK_j, TE::InputMapping::InputType::KeyJ));
        map.insert(std::make_pair(XK_k, TE::InputMapping::InputType::KeyK));
        map.insert(std::make_pair(XK_l, TE::InputMapping::InputType::KeyL));
        map.insert(std::make_pair(XK_m, TE::InputMapping::InputType::KeyM));
        map.insert(std::make_pair(XK_n, TE::InputMapping::InputType::KeyN));
        map.insert(std::make_pair(XK_o, TE::InputMapping::InputType::KeyO));
        map.insert(std::make_pair(XK_p, TE::InputMapping::InputType::KeyP));
        map.insert(std::make_pair(XK_q, TE::InputMapping::InputType::KeyQ));
        map.insert(std::make_pair(XK_r, TE::InputMapping::InputType::KeyR));
        map.insert(std::make_pair(XK_s, TE::InputMapping::InputType::KeyS));
        map.insert(std::make_pair(XK_t, TE::InputMapping::InputType::KeyT));
        map.insert(std::make_pair(XK_u, TE::InputMapping::InputType::KeyU));
        map.insert(std::make_pair(XK_v, TE::InputMapping::InputType::KeyV));
        map.insert(std::make_pair(XK_w, TE::InputMapping::InputType::KeyW));
        map.insert(std::make_pair(XK_x, TE::InputMapping::InputType::KeyX));
        map.insert(std::make_pair(XK_y, TE::InputMapping::InputType::KeyY));
        map.insert(std::make_pair(XK_z, TE::InputMapping::InputType::KeyZ));
        map.insert(std::make_pair(XK_F1, TE::InputMapping::InputType::KeyF1));
        map.insert(std::make_pair(XK_F2, TE::InputMapping::InputType::KeyF2));
        map.insert(std::make_pair(XK_F3, TE::InputMapping::InputType::KeyF3));
        map.insert(std::make_pair(XK_F4, TE::InputMapping::InputType::KeyF4));
        map.insert(std::make_pair(XK_F5, TE::InputMapping::InputType::KeyF5));
        map.insert(std::make_pair(XK_F6, TE::InputMapping::InputType::KeyF6));
        map.insert(std::make_pair(XK_F7, TE::InputMapping::InputType::KeyF7));
        map.insert(std::make_pair(XK_F8, TE::InputMapping::InputType::KeyF8));
        map.insert(std::make_pair(XK_F9, TE::InputMapping::InputType::KeyF9));
        map.insert(std::make_pair(XK_F10, TE::InputMapping::InputType::KeyF10));
        map.insert(std::make_pair(XK_F11, TE::InputMapping::InputType::KeyF11));
        map.insert(std::make_pair(XK_F12, TE::InputMapping::InputType::KeyF12));
        map.insert(std::make_pair(XK_Control_L, TE::InputMapping::InputType::KeyControlLeft));
        map.insert(std::make_pair(XK_Alt_L, TE::InputMapping::InputType::KeyAltLeft));
        map.insert(std::make_pair(XK_Shift_L, TE::InputMapping::InputType::KeyShiftLeft));
        map.insert(std::make_pair(XK_space, TE::InputMapping::InputType::KeySpace));
        map.insert(std::make_pair(XK_Return, TE::InputMapping::InputType::KeyEnter));
        map.insert(std::make_pair(XK_Escape, TE::InputMapping::InputType::KeyEscape));
        map.insert(std::make_pair(XK_BackSpace, TE::InputMapping::InputType::KeyBackspace));
        map.insert(std::make_pair(XK_Tab, TE::InputMapping::InputType::KeyTab));
        //map.insert(std::make_pair(VK_SEPARATOR, TE::InputMapping::InputType::KeySeperator)); Whats this?
        map.insert(std::make_pair(XK_Caps_Lock, TE::InputMapping::InputType::KeyCapslock));
        map.insert(std::make_pair(XK_Up, TE::InputMapping::InputType::KeyUp));
        map.insert(std::make_pair(XK_Down, TE::InputMapping::InputType::KeyDown));
        map.insert(std::make_pair(XK_Left, TE::InputMapping::InputType::KeyLeft));
        map.insert(std::make_pair(XK_Right, TE::InputMapping::InputType::KeyRight));
        map.insert(std::make_pair(XK_Page_Up, TE::InputMapping::InputType::KeyPgUp));
        map.insert(std::make_pair(XK_Page_Down, TE::InputMapping::InputType::KeyPgDown));
        map.insert(std::make_pair(XK_Home, TE::InputMapping::InputType::KeyHome));
        map.insert(std::make_pair(XK_End, TE::InputMapping::InputType::KeyEnd));
        map.insert(std::make_pair(XK_KP_0, TE::InputMapping::InputType::KeyNum0));
        map.insert(std::make_pair(XK_KP_1, TE::InputMapping::InputType::KeyNum1));
        map.insert(std::make_pair(XK_KP_2, TE::InputMapping::InputType::KeyNum2));
        map.insert(std::make_pair(XK_KP_3, TE::InputMapping::InputType::KeyNum3));
        map.insert(std::make_pair(XK_KP_4, TE::InputMapping::InputType::KeyNum4));
        map.insert(std::make_pair(XK_KP_5, TE::InputMapping::InputType::KeyNum5));
        map.insert(std::make_pair(XK_KP_6, TE::InputMapping::InputType::KeyNum6));
        map.insert(std::make_pair(XK_KP_7, TE::InputMapping::InputType::KeyNum7));
        map.insert(std::make_pair(XK_KP_8, TE::InputMapping::InputType::KeyNum8));
        map.insert(std::make_pair(XK_KP_9, TE::InputMapping::InputType::KeyNum9));
        map.insert(std::make_pair(XK_colon, TE::InputMapping::InputType::KeyCollon));
        map.insert(std::make_pair(XK_plus, TE::InputMapping::InputType::KeyPlus));
        map.insert(std::make_pair(XK_comma, TE::InputMapping::InputType::KeyComma));
        map.insert(std::make_pair(XK_minus, TE::InputMapping::InputType::KeyMinus));
        map.insert(std::make_pair(XK_period, TE::InputMapping::InputType::KeyPeriod));
        map.insert(std::make_pair(XK_slash, TE::InputMapping::InputType::KeySlashQuest));
        map.insert(std::make_pair(XK_asciitilde, TE::InputMapping::InputType::KeyTilde));
        //map.insert(std::make_pair(X, TE::InputMapping::InputType::MouseLButton));
        //map.insert(std::make_pair(VK_MBUTTON, TE::InputMapping::InputType::MouseRButton));
        //map.insert(std::make_pair(VK_RBUTTON, TE::InputMapping::InputType::MouseRButton));
    }
}

TE::Platform::PlatformWindow::PlatformWindow( XID windowXID,
                                              IO::FileIO & fileIO,
                                              const std::string & windowTitle )
    : m_fullscreen(false)
    , m_width(640)
    , m_height(480)
    , m_externalWindow(true)
    , m_windowTitle(windowTitle)
    , m_colorBits(32)
    , m_setResolutionCalled(false)
    , m_pointerMode(PointerMode::Free)
    , m_inputMapper(fileIO)
{
    XSetErrorHandler(::XErrorHandlerFunction);
    ::SetupMapping(m_platformTEngineMapping);
}

TE::Platform::PlatformWindow::PlatformWindow(IO::FileIO &fileIO,
                                             const std::string & windowTitle)
    : m_fullscreen(false)
    , m_width(640)
    , m_height(480)
    , m_externalWindow(false)
    , m_windowTitle(windowTitle)
    , m_colorBits(32)
    , m_setResolutionCalled(false)
    , m_pointerMode(PointerMode::Free)
    , m_inputMapper(fileIO)
{
    XSetErrorHandler(::XErrorHandlerFunction);
    ::SetupMapping(m_platformTEngineMapping);
}

TE::Platform::PlatformWindow::~PlatformWindow()
{

}

void TE::Platform::PlatformWindow::LoadInputFile(const std::string &filePath)
{
    m_inputMapper.LoadInputFile(filePath);
}

void TE::Platform::PlatformWindow::Initialize()
{
    if (!m_externalWindow)
    {
        m_xlibDisplay = XOpenDisplay(nullptr);
        if (!m_xlibDisplay)
        {
            //LOG FATAL ERROR
            std::exit(0);
        }

        m_xlibRootWindowID = DefaultRootWindow(m_xlibDisplay);

        Colormap cmap;
        XVisualInfo * visualInfo = GetVisualInfo();
        cmap = XCreateColormap(m_xlibDisplay,
                               m_xlibRootWindowID,
                               visualInfo->visual,
                               AllocNone);

        XSetWindowAttributes swa;
        swa.colormap = cmap;
        swa.event_mask = KeyPressMask |
                         KeyReleaseMask |
                         ButtonPressMask |
                         ButtonReleaseMask |
                         PointerMotionMask |
                         EnterWindowMask |
                         StructureNotifyMask;

        m_xlibWindowID = XCreateWindow(m_xlibDisplay,
                                       m_xlibRootWindowID,
                                       0,
                                       0,
                                       m_width,
                                       m_height,
                                       0,
                                       visualInfo->depth,
                                       InputOutput,
                                       visualInfo->visual,
                                       CWColormap | CWEventMask,
                                       &swa);

        XMapWindow(m_xlibDisplay, m_xlibWindowID);
        XStoreName(m_xlibDisplay, m_xlibWindowID, m_windowTitle.c_str());

        m_xlibwmDeleteAtom = XInternAtom(m_xlibDisplay, "WM_DELETE_WINDOW", false);
        XSetWMProtocols(m_xlibDisplay, m_xlibWindowID, &m_xlibwmDeleteAtom, 1);
    }

    OnOpenWindow();

    SetResolution(false, m_width, m_height, 32, -1, -1);
}

void TE::Platform::PlatformWindow::Cleanup()
{
    OnCloseWindow();

    if(m_fullscreen)
        SwitchToWindowed();

    XUngrabPointer(m_xlibDisplay, CurrentTime);

    XDestroyWindow(m_xlibDisplay, m_xlibWindowID);
    XCloseDisplay(m_xlibDisplay);
}

TE::InputMapping::InputMapper &TE::Platform::PlatformWindow::GetInputMapper()
{
    return m_inputMapper;
}

void TE::Platform::PlatformWindow::SetResolution(bool fullscreen, I32 width, I32 height, I32 colorBits , I32 positionX, I32 positionY)
{
    m_width = width;
    m_height = height;
    m_colorBits = colorBits;
    m_positionX = positionX;
    m_positionY = positionY;

    if(!m_externalWindow)
    {
        I32 x;
        I32 y;

        if (fullscreen)
        {
            x = y = 0;

            if(!m_fullscreen)
                SwitchToFullscreen();
        }
        else
        {
            if(positionX == -1 || positionY == -1)
            {
                x = (GetScreenWidth() - width) / 2;
                y = (GetScreenHeight() - height) / 2;
            }
            else
            {
                x = positionX;
                y = positionY;
            }

            if(m_fullscreen)
                SwitchToWindowed();
        }
        XMoveResizeWindow(m_xlibDisplay,
                          m_xlibWindowID,
                          x,
                          y,
                          m_width,
                          m_height);

        XMapRaised(m_xlibDisplay,
                   m_xlibWindowID);
    }

    m_setResolutionCalled = true;
}

void TE::Platform::PlatformWindow::SetSize(I32 width, I32 height)
{
    m_width = width;
    m_height = height;
    if(m_xlibDisplay)
        SetResolution(false, m_width, m_height, 32, m_positionX, m_positionY);
}

void TE::Platform::PlatformWindow::SetPosition(I32 x, I32 y)
{
    m_positionX = x;
    m_positionY = y;
    if(m_xlibDisplay)
        SetResolution(false, m_width, m_height, 32, m_positionX, m_positionY);
}

void TE::Platform::PlatformWindow::SetFullscreen(bool fullscreen)
{
    m_fullscreen = fullscreen;
    if(m_xlibDisplay)
        SetResolution(false, m_width, m_height, 32, m_positionX, m_positionY);
}

void TE::Platform::PlatformWindow::SwitchToFullscreen()
{
    Hints hints;
    hints.flags = 2;
    hints.decorations = false;
    Atom borderlessProperty = XInternAtom(m_xlibDisplay,
                                          "_MOTIF_WM_HINTS",
                                          true);
    XChangeProperty(m_xlibDisplay,
                    m_xlibWindowID,
                    borderlessProperty,
                    borderlessProperty,
                    32,
                    PropModeReplace,
                    reinterpret_cast<U8*>(&hints),
                    5);

    I32 screen = DefaultScreen(m_xlibDisplay);
    XF86VidModeModeInfo **modes;
    I32 numModes;
    XF86VidModeGetAllModeLines(m_xlibDisplay, screen, &numModes, &modes);
    m_desktopMode = *modes[0];

    I32 selected = 0;
    for(I32 i = 0; i < numModes; ++i)
    {
        if(modes[i]->hdisplay == m_width && modes[i]->vdisplay == m_height)
            selected = i;
    }

    XF86VidModeSwitchToMode(m_xlibDisplay,
                            screen,
                            modes[selected]);
    XFree(modes);
    XF86VidModeSetViewPort(m_xlibDisplay,
                           screen,
                           0,
                           0);

    m_fullscreen = true;
}

void TE::Platform::PlatformWindow::SwitchToWindowed()
{
    Hints hints;
    hints.flags = 2;
    hints.decorations = true;
    Atom borderlessProperty = XInternAtom(m_xlibDisplay,
                                          "_MOTIF_WM_HINTS",
                                          true);
    XChangeProperty(m_xlibDisplay,
                    m_xlibWindowID,
                    borderlessProperty,
                    borderlessProperty,
                    32,
                    PropModeReplace,
                    reinterpret_cast<U8*>(&hints),
                    5);
    I32 screen = DefaultScreen(m_xlibDisplay);
    XF86VidModeSwitchToMode(m_xlibDisplay, screen, &m_desktopMode);
    XF86VidModeSetViewPort(m_xlibDisplay, screen, 0, 0);

    m_fullscreen = false;
}

I32 TE::Platform::PlatformWindow::GetWindowWidth()
{
    return m_width;
}

I32 TE::Platform::PlatformWindow::GetWindowHeight()
{
    return m_height;
}

I32 TE::Platform::PlatformWindow::GetScreenWidth()
{
    int screen = DefaultScreen(m_xlibDisplay);
    return XDisplayWidth(m_xlibDisplay, screen);
}

I32 TE::Platform::PlatformWindow::GetScreenHeight()
{
    int screen = DefaultScreen(m_xlibDisplay);
    return XDisplayHeight(m_xlibDisplay, screen);
}

bool TE::Platform::PlatformWindow::MessageLoop()
{
    bool quitMessageReceived = false;

    static I32 previousMousePos[] = { 0,0 };
    static bool previousKeyState[InputMapping::InputType::Count] = { false };

    m_asciiInput.clear();

    while(XPending(m_xlibDisplay))
    {
        XNextEvent(m_xlibDisplay, &m_xlibEvent);
        switch(m_xlibEvent.type)
        {
        case ConfigureNotify:
            {
                SetPointerPosition(m_width / 2, m_height / 2);
            }
            break;
        case EnterNotify:
            m_previousMousePosValid = false;
            break;
        case ClientMessage:
            {
                if(static_cast<Atom>(m_xlibEvent.xclient.data.l[0]) == m_xlibwmDeleteAtom)
                {
                    quitMessageReceived = true;
                }
            }
            break;
        case MotionNotify:
            {
                I32 x = m_xlibEvent.xmotion.x;
                I32 y = m_xlibEvent.xmotion.y;

                if(!m_previousMousePosValid)
                {
                    previousMousePos[0] = x;
                    previousMousePos[1] = y;
                    m_previousMousePosValid = true;
                }

                F64 normalizedX = static_cast<F64>(x) / m_width;
                F64 normalizedY = static_cast<F64>(y) / m_height;

                F64 normalizedDeltaX = static_cast<F64>(previousMousePos[0] - x) / m_width;
                F64 normalizedDeltaY = static_cast<F64>(previousMousePos[1] - y) / m_height;

                assert(normalizedDeltaX > -1.0 && normalizedDeltaX < 1.0 && "Oops, looks like this needs some debugging");
                assert(normalizedDeltaY > -1.0 && normalizedDeltaY < 1.0 && "Oops, looks like this needs some debugging");

                m_inputMapper.MapRangeInput(InputMapping::RangeInput::MouseX, normalizedX);
                m_inputMapper.MapRangeInput(InputMapping::RangeInput::MouseY, normalizedY);
                m_inputMapper.MapRangeInput(InputMapping::RangeInput::MouseDeltaX, normalizedDeltaX);
                m_inputMapper.MapRangeInput(InputMapping::RangeInput::MouseDeltaY, normalizedDeltaY);

                previousMousePos[0] = x;
                previousMousePos[1] = y;
            }
            break;
        case KeyPress:
            {
                auto findItr = m_platformTEngineMapping.find(XLookupKeysym(&m_xlibEvent.xkey, 0));
                if (findItr != m_platformTEngineMapping.end())
                {
                    bool pressed = true;
                    m_inputMapper.MapInput(findItr->second, pressed, previousKeyState[findItr->second]);
                    previousKeyState[findItr->second] = true;
                }
            }
            break;
        case KeyRelease:
            {
                auto findItr = m_platformTEngineMapping.find(XLookupKeysym(&m_xlibEvent.xkey, 0));
                if (findItr != m_platformTEngineMapping.end())
                {
                    bool pressed = false;
                    m_inputMapper.MapInput(findItr->second, pressed, previousKeyState[findItr->second]);
                    previousKeyState[findItr->second] = false;
                }
            }
            break;
        case ButtonPress:
            {

            }
            break;
        case ButtonRelease:
            {

            }
            break;
        default:
            //not handled
            break;
        }
    }

    m_inputMapper.Dispatch();

    return quitMessageReceived;
}

void TE::Platform::PlatformWindow::SetWindowTitle(const std::string &title)
{
    m_windowTitle = title;
    if(m_xlibDisplay)
        XStoreName(m_xlibDisplay, m_xlibWindowID, m_windowTitle.c_str());
}

bool TE::Platform::PlatformWindow::IsFullscreen()
{
    return m_fullscreen;
}

std::vector<char> TE::Platform::PlatformWindow::GetAsciiInput()
{
    return m_asciiInput;
}

void TE::Platform::PlatformWindow::SetPointerMode(TE::Platform::PointerMode pointerMode)
{
    m_pointerMode = pointerMode;
    if(m_pointerMode == PointerMode::Grabbed)
    {
        XGrabPointer(m_xlibDisplay,
                     m_xlibWindowID,
                     true,
                     ButtonPressMask,
                     GrabModeAsync,
                     GrabModeAsync,
                     m_xlibWindowID,
                     0,
                     CurrentTime);
        m_previousMousePosValid = false;
    }
}

void TE::Platform::PlatformWindow::SetPointerPosition(I32 x, I32 y)
{
    XWarpPointer(m_xlibDisplay,
                 0,
                 m_xlibWindowID,
                 0,
                 0,
                 0,
                 0,
                 x,
                 y);
    while(XCheckTypedWindowEvent(m_xlibDisplay,
                                 m_xlibWindowID,
                                 MotionNotify,
                                 &m_xlibEvent));
}

XID TE::Platform::PlatformWindow::GetWindowXID()
{
    return m_xlibWindowID;
}

Display *TE::Platform::PlatformWindow::GetDisplay()
{
    return m_xlibDisplay;
}
