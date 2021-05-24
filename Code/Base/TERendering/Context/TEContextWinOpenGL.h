#ifndef TECONTEXTOPENGL_H
#define TECONTEXTOPENGL_H

#include "TEDataTypes.h"
#include "TEWinWindow.h"

#include <vector>
#include <windows.h>

namespace TE::InputMapping {
    class InputMapper;
}

namespace TE::Context {
    class APIContext : public Platform::PlatformWindow {
      public:
        APIContext(Platform::OSWinId osWinId,
                   IO::FileIO &fileIO,
                   const std::string &windowName = "TEngine");
        APIContext(IO::FileIO &fileIO, const std::string &windowName = "TEngine");
        virtual ~APIContext();
        void SetCGContext(/*CGcontext& cgContext*/);
        void BeginFrame();
        void EndFrame();

      private:
        virtual void OnOpenWindow();
        virtual void OnCloseWindow();
        // CGcontext m_cgContext;
        HDC m_hdc;
        std::vector<HGLRC> m_hrcs;
    };
}

#endif
