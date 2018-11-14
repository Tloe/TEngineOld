/*#include <TEDefines.h>

#if TEWINDOWS

#ifndef TEWINDOWWINOGL_H
#define TEWINDOWWINOGL_H

#include <TEWindow.h>
#include <windows.h>
#include <exception>
#include <string>
#include <gl/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>

namespace TE
{
	namespace Render
	{
		class WindowWinOgl : public Window
		{
		public:
			WindowWinOgl(HINSTANCE &hInstance, int nCmdShow, const WindowInf& winInf);

			~WindowWinOgl();

			bool Initialize();

			bool DeInitialize();

			void NextFrame();

			bool InitWindow();

			bool InitContext();

			void TestDrawFunc();

			static LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

		private:
			//Window
			int			m_nCmdShow;
			HINSTANCE	m_hInstance;
			HWND		m_hWnd;
			
			//Context
			HDC			m_hdc;
			HGLRC		m_hrc;
		};
	}
}

#endif

#endif
*/