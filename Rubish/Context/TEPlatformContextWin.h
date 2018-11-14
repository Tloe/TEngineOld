#ifndef TEPLATFORMCONTEXTWIN_H
#define TEPLATFORMCONTEXTWIN_H

#include "TEInput.h"
#include <map>
#include <windows.h>
#include "TEDataTypes.h"

namespace TE
{
	namespace Context
	{
		class PlatformContext
		{
			//friend class APIContext;
		public:
			PlatformContext(HWND hwnd);
			PlatformContext();
			void Init();
			void Cleanup();
			void BeginFrame();
			void EndFrame();
			void SetResolution(bool fullscreen, I32 width = 640, I32 height = 480, I32 colorBits = 32);
			I32  GetWindowWidth();
			I32  GetWindowHeight();
			I32	 GetScreenWidth();
			I32	 GetScreenHeight();
			HWND GetHWND();
		private:
			void SwitchToFullscreen();
			void SwitchToWindowed();
			void InitInputMap();
			Enum m_previouseInputState[100];
			I32 m_previouseMousePos[2];
			std::map<I32, Enum> m_platformTEInputMap;
			
			I32 m_width;
			I32 m_height;
			I32 m_colorBits;
			bool m_fullscreen;
			bool m_externalWindow;
			HWND m_hWnd;
			HDC m_hdc;
			HINSTANCE m_hInstance;
			DWORD m_dwWindowStyle;
			static std::map<HWND, PlatformContext*>	s_allWindows;
			static LRESULT CALLBACK WndProc( HWND hWnd, U32 message, WPARAM wParam, LPARAM lParam );
			virtual LRESULT DoWndProc(HWND hWnd, U32 message, WPARAM wParam, LPARAM lParam);
			void AddhWndWinReference(HWND hWnd, PlatformContext* contextRef);
		};
	}
}

#endif