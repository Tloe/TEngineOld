#ifndef TEWINWINDOW_H
#define TEWINWINDOW_H

#include <TEDataTypes.h>
#include <TEInput.h>
#include <TEInputMapper.h>

#include <unordered_map>
#include <vector>
#include <string>
#include <atomic>
#include <queue>
#include <windows.h>

namespace TE
{
    namespace IO { class FileIO; }

	namespace Platform
    {
        typedef HWND OSWinId;

		class PlatformWindow
		{
		public:
            PlatformWindow(OSWinId hwnd,
                           IO::FileIO & fileIO,
                           const std::string & windowName = "TEngine");
            PlatformWindow(IO::FileIO & fileIO,
						   const std::string & windowName = "TEngine");
            virtual ~PlatformWindow();

			virtual void SetResolution(bool fullscreen, I32 width, I32 height, I32 colorBits, I32 positionX, I32 positionY);
			void LoadInputFile(const std::string& filePath);
            void Initialize();
            void Cleanup();
			InputMapping::InputMapper& GetInputMapper();
            bool MessageLoop();
			I32  GetWindowWidth();
			I32  GetWindowHeight();
			I32	 GetScreenWidth();
			I32	 GetScreenHeight();
			HWND GetHWND();
			bool IsFullscreen();
			std::vector<char> GetAsciiInput();
			void SetWindowTitle(const std::string & title);

		private:
			typedef std::unordered_map<I32, Enum> PlatformEngineInputMap;

			virtual void OnOpenWindow() = 0;
			virtual void OnCloseWindow() = 0;
			void SwitchToFullscreen();
			void SwitchToWindowed();
			void SetupPlatformInputMap();
			LRESULT DoWndProc(HWND hWnd, U32 message, WPARAM wParam, LPARAM lParam);
			void HandleDownState(Enum input);
			void HandleUpState(Enum input);
			void HandleDoubleClickState(Enum input);
			static LRESULT CALLBACK WndProc( HWND hWnd, U32 message, WPARAM wParam, LPARAM lParam );
			
            InputMapping::InputMapper m_inputMapper;
			PlatformEngineInputMap m_platformTEInputMap;
			std::vector<char> m_asciiInput;
			I32 m_previouseMousePos[2];
			std::string m_windowTitle;
			I32 m_width;
			I32 m_height;
			I32 m_x;
			I32 m_y;
			I32 m_colorBits;
			bool m_fullscreen;
			bool m_externalWindow;
			std::atomic<bool> m_setResolutionCalled;
			std::atomic<bool> m_quitMessageReceived;
			HWND m_hWnd;
			HDC m_hdc;
			HINSTANCE m_hInstance;
			DWORD m_dwWindowStyle;
			static std::unordered_map<HWND, PlatformWindow*> s_hwndPlatformWindowMap;
		};
	}
}

#endif
