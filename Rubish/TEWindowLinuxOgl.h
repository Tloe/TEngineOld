/*#include <TEDefines.h>

#if TELINUX

#ifndef TEWINDOWLINUXOGL_H
#define TEWINDOWLINUXOGL_H

#include <TEWindow.h>
#include <stdlib.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>

namespace TE
{
	namespace Render
	{
		class WindowLinuxOgl : public Window
		{
		public:
			WindowLinuxOgl(const WindowInf& winInf);

			~WindowLinuxOgl();

			bool Initialize();

			bool DeInitialize();

			void NextFrame();
			
			void TestDrawFunc();

			bool InitWindow();

			bool InitContext();

		private:
            XVisualInfo *m_vi;
			Display		*m_dpy;
			XID          m_rootWindow;
			XID          m_window;
			GLXContext   m_glc;
			XEvent       *m_xev;
		};
	}

}

#endif

#endif
*/