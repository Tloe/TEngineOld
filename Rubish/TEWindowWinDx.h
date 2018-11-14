/*#include <TEDefines.h>

#if TEWINDOWS

#ifndef TEWINDOWWINDX_H
#define TEWINDOWWINDX_H

#include <TEWindow.h>
#include <windows.h>
#include <exception>
#include <string>
#include <d3d11.h>
#include <d3dx11.h>

namespace TE
{
	namespace Render
	{
		class WindowWinDx : public Window
		{
		public:
			WindowWinDx(HINSTANCE &hInstance, int nCmdShow, const WindowInf& winInf);

			~WindowWinDx();

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
			D3D_FEATURE_LEVEL		m_featureLevel;
			ID3D11Device*			m_pd3dDevice;
			ID3D11DeviceContext*	m_pImmediateContext;
			IDXGISwapChain*			m_pSwapChain;
			ID3D11RenderTargetView*	m_pRenderTargetView;
		};
	}
}

#endif

#endif
*/