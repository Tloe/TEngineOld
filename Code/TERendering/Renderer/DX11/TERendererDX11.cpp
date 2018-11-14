#include <TERendererDX11.h>
#include <TEMatrix4D.h>
#include "TEContextWinDX11.h"
#include "TEColor.h"
#include "TEVertexBufferLayoutDX11.h"
#include "TEVertexBufferDX11.h"
#include "TEIndexBufferDX11.h"
#include "TETexture2DDX11.h"
#include "TEEffect.h"
#include "TEPlatformWindowIncludes.h"

TE::Render::APIRenderer::APIRenderer(Context::APIContext& apiContext)
	:
	m_apiContext(apiContext)
{

}

TE::Render::APIRenderer::~APIRenderer()
{

}

void TE::Render::APIRenderer::Initialize(CGcontext& cgContext)
{
	m_apiContext.SetCGContext(cgContext);
    m_apiContext.Initialize();
	SetViewPort(0 , 0, 640, 480);
}

void TE::Render::APIRenderer::Cleanup()
{
    m_apiContext.Cleanup();
}

void TE::Render::APIRenderer::BeginFrame(const ColorRGBA& clearColor)
{
	m_apiContext.BeginFrame();
	m_apiContext.GetDeviceContext()->ClearRenderTargetView(m_apiContext.GetBackBuffer(), &clearColor.r );
	m_apiContext.GetDeviceContext()->ClearDepthStencilView(m_apiContext.GetDepthStencilView(), D3D11_CLEAR_DEPTH, 1.0f, 0 );
}

void TE::Render::APIRenderer::EndFrame()
{
	DXGI_PRESENT_PARAMETERS parameters = {0};
	parameters.DirtyRectsCount = 0;
	parameters.pDirtyRects = nullptr;
	parameters.pScrollRect = nullptr;
	parameters.pScrollOffset = nullptr;

	m_apiContext.GetSwapChain()->Present1( 1, 0, &parameters);
	m_apiContext.EndFrame();
}

void TE::Render::APIRenderer::Draw( I32 indexCount )
{
	m_apiContext.GetDeviceContext()->RSSetState(m_apiContext.GetRasterizerState());
	m_apiContext.GetDeviceContext()->DrawIndexed(indexCount, 0, 0);
}

void TE::Render::APIRenderer::SetViewPort( I32 x, I32 y, I32 width, I32 height )
{
	D3D11_VIEWPORT vp;
	vp.Width = static_cast<F32>(width);
	vp.Height = static_cast<F32>(height);
	vp.MinDepth = Math::Base<Real>::REAL_ZERO;
	vp.MaxDepth = Math::Base<Real>::REAL_ONE;
	vp.TopLeftX = static_cast<F32>(x);
	vp.TopLeftY = static_cast<F32>(y);
	m_apiContext.GetDeviceContext()->RSSetViewports( 1, &vp );
}

void TE::Render::APIRenderer::SetResolution(I32 width, I32 height, I32 viewportWidth, I32 viewportHeight, bool fullscreen, bool updateViewport, I32 positionX, I32 positionY)
{	
	m_apiContext.SetResolution(fullscreen, width, height, 32, positionX, positionY);

	if (updateViewport) SetViewPort(0,0, viewportWidth, viewportHeight);
}

TE::Render::APIVertexBufferLayoutUPtr TE::Render::APIRenderer::CreateAPIVertexBufferLayout( const Mesh& mesh, const Effect& effect )
{
    return std::make_unique<APIVertexBufferLayout>(m_apiContext, mesh, effect);
}

TE::Render::APIVertexBufferUPtr TE::Render::APIRenderer::CreateAPIVertexBuffer( const Mesh& mesh )
{
    return std::make_unique<APIVertexBuffer>(m_apiContext, mesh);
}

TE::Render::APIIndexBufferUPtr TE::Render::APIRenderer::CreateAPIIndexBuffer( const Mesh& mesh )
{
    return std::make_unique<APIIndexBuffer>(m_apiContext, mesh);
}

TE::Render::APITexture2DUPtr TE::Render::APIRenderer::CreateAPITexture2D( Texture& texture, Effect& effect )
{
    return STD::make_unique<APITexture2D>(m_apiContext, texture, effect.GetCGParamaeter("texSampler0"));
}
