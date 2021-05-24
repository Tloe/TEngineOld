#ifndef TELINUXWINDOW_H
#define TELINUXWINDOW_H

#include "TEDataTypes.h"
#include "TEInput.h"
#include "TEInputMapper.h"

#include <atomic>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

#include <X11/X.h>
#undef None
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/xf86vmode.h>

namespace TE::IO {
    class FileIO;
}

namespace TE::Platform {
    typedef XID OSWinId;

    enum class PointerMode { Free, Locked, Grabbed };

    class PlatformWindow {
      public:
        PlatformWindow(OSWinId windowXID,
                       IO::FileIO &fileIO,
                       const std::string &windowTitle = "TEngine");
        PlatformWindow(IO::FileIO &fileIO, const std::string &windowTitle = "TEngine");
        virtual ~PlatformWindow();

        void LoadInputFile(const std::string &filePath);
        void Initialize();
        void Cleanup();
        InputMapping::InputMapper &GetInputMapper();
        bool MessageLoop();
        void SetWindowTitle(const std::string &title);
        void SetResolution(bool fullscreen,
                           I32 width,
                           I32 height,
                           I32 colorBits,
                           I32 positionX,
                           I32 positionY);
        void SetSize(I32 widht, I32 height);
        void SetPosition(I32 x, I32 y);
        void SetFullscreen(bool fullscreen);

        I32 GetWindowWidth();
        I32 GetWindowHeight();
        I32 GetScreenWidth();
        I32 GetScreenHeight();
        bool IsFullscreen();
        std::vector<char> GetAsciiInput();
        void SetPointerMode(PointerMode pointerMode);
        void SetPointerPosition(I32 x, I32 y);

      protected:
        XID GetWindowXID();
        Display *GetDisplay();

      private:
        typedef std::unordered_map<I32, InputMapping::InputType> PlatformEngineInputMap;

        virtual void OnOpenWindow()          = 0;
        virtual void OnCloseWindow()         = 0;
        virtual XVisualInfo *GetVisualInfo() = 0;

        void SwitchToFullscreen();
        void SwitchToWindowed();
        void SetupPlatformInputMap();

        void ClearInputQues();

        bool m_fullscreen;
        I32 m_width;
        I32 m_height;
        I32 m_positionX;
        I32 m_positionY;
        bool m_externalWindow;
        std::string m_windowTitle;
        I32 m_colorBits;
        std::atomic<bool> m_setResolutionCalled;
        std::atomic<bool> m_quitMessageReceived;
        XID m_xlibWindowID;
        XID m_xlibRootWindowID;
        Display *m_xlibDisplay;
        XEvent m_xlibEvent;
        Atom m_xlibwmDeleteAtom;
        XF86VidModeModeInfo m_desktopMode;

        PointerMode m_pointerMode;
        InputMapping::InputMapper m_inputMapper;
        PlatformEngineInputMap m_platformTEngineMapping;
        std::vector<char> m_asciiInput;
        bool m_previousMousePosValid;
    };
}

#endif
