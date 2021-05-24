/*	This file is only inluded in the renderer if we want a linux opengl context.
 *	Controlled by the TE_WINDOWS define
 */

#ifndef TECONTEXTLINUXOPENGL_H
#define TECONTEXTLINUXOPENGL_H

#include "TELinuxWindow.h"
#include "TEOpenGL.h"

namespace TE::Context {
    class APIContext : public Platform::PlatformWindow {
      public:
        APIContext(Platform::OSWinId hwnd,
                   IO::FileIO &fileIO,
                   const std::string &windowName = "TEngine");
        APIContext(IO::FileIO &fileIO, const std::string &windowName = "TEngine");
        ~APIContext();

        void SetCGContext(/*CGcontext& cgContext*/);
        virtual void OnOpenWindow();
        virtual void OnCloseWindow();
        virtual XVisualInfo *GetVisualInfo();
        void BeginFrame();
        void EndFrame();

      private:
        GLXContext m_glContext;
        XID m_xlibWindowXID;
        XVisualInfo *m_xlibVisualInfo;
        /* CGcontext m_cgContext; */
    };
}

#endif
