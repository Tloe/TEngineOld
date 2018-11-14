#ifndef TECONTEXTWIN_H
#define TECONTEXTWIN_H

#include <TEWindow.h>
#include <windows.h>
#include <map>

namespace TE
{
	namespace Context
	{
		class WindowWin
		{
		public:
			Window& GetWindowRef();
		protected:
			WindowWin();
			virtual ~WindowWin();
			
			virtual void Init(Window& window);
			virtual void Cleanup();
			virtual void BeginFrame();
			virtual void EndFrame() = 0;

			HWND GetHWND();
		private:
			Window		m_window;
			
			static LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
			virtual LRESULT DoWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			void AddhWndWinReference(HWND hWnd, WindowWin* windowRef);

			HWND									m_hWnd;
			HINSTANCE								m_hInstance;
			static std::map<HWND, WindowWin*>		s_allWindows;
		};
	}
}

#endif
