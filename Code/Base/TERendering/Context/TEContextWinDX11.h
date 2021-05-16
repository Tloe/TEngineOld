#ifndef TECONTEXTDX11_H
#define TECONTEXTDX11_H

#include "TEDataTypes.h"
#include "TEWinWindow.h"

#include <d3d11.h>
#include <d3d11_1.h>
#include <d3dcommon.h>
#include <dxgi.h>

namespace TE {
namespace Context {
    class APIContext : public Platform::PlatformWindow {
      public:
        APIContext(Platform::OSWinId osWinId, IO::FileIO &fileIO, const std::string &windowName = "TEngine");
        APIContext(IO::FileIO &fileIO, const std::string &windowName = "TEngine");
        virtual ~APIContext();

        virtual void SetResolution(bool fullscreen, I32 width, I32 height, I32 colorBits, I32 positionX, I32 positionY);
        void BeginFrame();
        void EndFrame();
        void SetCGContext(/*CGcontext& cgContext*/);

        ID3D11Device1 *GetDevice();
        ID3D11DeviceContext1 *GetDeviceContext();
        ID3D11RenderTargetView *GetBackBuffer();
        ID3D11DepthStencilView *GetDepthStencilView();
        IDXGISwapChain1 *GetSwapChain();
        ID3D11RasterizerState *GetRasterizerState();

      private:
        void OnOpenWindow();
        void OnCloseWindow();
        void CreateSwapChain();
        void CreateBackBuffer();
        void CreateDepthStencilBufferAndView();
        void CreateRasterizerState();

        // CGcontext m_cgContext;
        D3D_FEATURE_LEVEL m_d3dFeatureLevel;
        ID3D11Device1 *m_d3dDevice;
        ID3D11DeviceContext1 *m_d3dDeviceContext;
        IDXGISwapChain1 *m_d3dSwapChain;
        ID3D11RenderTargetView *m_d3dBackBuffer;
        ID3D11DepthStencilView *m_d3dDepthStencilView;
        ID3D11Texture2D *m_d3dDepthStencilBuffer;
        ID3D11RasterizerState *m_d3dRState;
        bool m_initialized;
    };
}
}

#endif
