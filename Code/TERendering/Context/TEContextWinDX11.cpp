#include <TEContextWinDX11.h>
#include "TEMathBase.h"
#include <TEDataTypes.h>
#include <Cg/cgD3D11.h>
#include <dxgi1_2.h>
#include <d3d11.h>
#include <TEPlatformWindowIncludes.h>

TE::Context::APIContext::APIContext(OSWinId osWinId,
                                    IO::FileIO & fileIO,
									const std::string& windowName /*= "TEngine"*/ )
    : PlatformWindow(osWinId, fileIO, windowName)
{

}

TE::Context::APIContext::APIContext(IO::FileIO &fileIO,
                                    const std::string& windowName /*= "TEngine"*/ )
    : PlatformWindow(fileIO, windowName)
{

}

TE::Context::APIContext::~APIContext()
{

}

void TE::Context::APIContext::SetCGContext(CGcontext& cgContext)
{
	m_cgContext = cgContext;
}

void TE::Context::APIContext::OnOpenWindow()
{
	m_initialized = true;

	CreateSwapChain();

	CreateBackBuffer();

	CreateDepthStencilBufferAndView();

	m_d3dDeviceContext->OMSetRenderTargets( 1, &m_d3dBackBuffer, m_d3dDepthStencilView);

	CreateRasterizerState();

	HRESULT hr = cgD3D11SetDevice(m_cgContext, m_d3dDevice);
	if( hr != S_OK )
		exit(1);
	cgD3D11RegisterStates(m_cgContext);
	cgD3D11SetManageTextureParameters(m_cgContext, CG_TRUE);
}

void TE::Context::APIContext::OnCloseWindow()
{
	cgD3D11SetDevice(m_cgContext,0);

	if( m_d3dDeviceContext ) m_d3dDeviceContext->ClearState();

	if( m_d3dBackBuffer ) m_d3dBackBuffer->Release();
	if(	m_d3dSwapChain ) m_d3dSwapChain->Release();
	if( m_d3dDeviceContext ) m_d3dDeviceContext->Release();
	if( m_d3dDevice ) m_d3dDevice->Release();
}

void TE::Context::APIContext::BeginFrame()
{

}

void TE::Context::APIContext::EndFrame()
{

}

ID3D11Device1* TE::Context::APIContext::GetDevice()
{
	return m_d3dDevice;
}

ID3D11DeviceContext1* TE::Context::APIContext::GetDeviceContext()
{
	return m_d3dDeviceContext;
}

ID3D11RenderTargetView* TE::Context::APIContext::GetBackBuffer()
{
	return m_d3dBackBuffer;
}

ID3D11DepthStencilView* TE::Context::APIContext::GetDepthStencilView()
{
	return m_d3dDepthStencilView;
}

IDXGISwapChain1* TE::Context::APIContext::GetSwapChain()
{
	return m_d3dSwapChain;
}

ID3D11RasterizerState* TE::Context::APIContext::GetRasterizerState()
{
	return m_d3dRState;
}

void TE::Context::APIContext::CreateSwapChain()
{
	HRESULT hr = S_OK;

	unsigned createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	unsigned numDriverTypes = ARRAYSIZE( driverTypes );

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		//D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	unsigned numFeatureLevels = ARRAYSIZE( featureLevels );

	D3D_DRIVER_TYPE driverType;
	for( U32 driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ )
	{
		driverType = driverTypes[driverTypeIndex];
		
		ID3D11Device* device;
		ID3D11DeviceContext* deviceContext;
		hr = D3D11CreateDevice(NULL,
			driverType,
			nullptr,
			createDeviceFlags,
			featureLevels,
			numFeatureLevels,
			D3D11_SDK_VERSION,
			&device,
			&m_d3dFeatureLevel,
			&deviceContext);
		if( SUCCEEDED( hr ) )
		{
			m_d3dDevice = static_cast<ID3D11Device1*>(device);
			m_d3dDeviceContext = static_cast<ID3D11DeviceContext1*>(deviceContext);
			break;
		}
	}

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {0};
	swapChainDesc.Stereo = false;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
	swapChainDesc.Flags = 0;
	// Use automatic sizing.
	swapChainDesc.Width = 0;
	swapChainDesc.Height = 0;
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferCount = 2;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;	

	IDXGIDevice2* dxgiDevice;
	m_d3dDevice->QueryInterface(__uuidof(IDXGIDevice2), (void **)&dxgiDevice);
	dxgiDevice->SetMaximumFrameLatency(1);

	IDXGIAdapter* dxgiAdapter;
	dxgiDevice->GetAdapter(&dxgiAdapter);

	IDXGIFactory2* dxgiFactory;
	dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory));
	
	hr = dxgiFactory->CreateSwapChainForHwnd(m_d3dDevice,
											 GetHWND(),
											 &swapChainDesc,
											 nullptr,
											 nullptr,
											 &m_d3dSwapChain);

	if( FAILED( hr ) )
		//LOG FATAL ERROR
		exit(0);
}

void TE::Context::APIContext::CreateBackBuffer()
{
	// Create a render target view
	ID3D11Texture2D* pBackBuffer = NULL;
	HRESULT hr = m_d3dSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer );
	if( FAILED( hr ) )
		//LOG FATAL ERROR
		exit(0);

	hr = m_d3dDevice->CreateRenderTargetView( pBackBuffer, NULL, &m_d3dBackBuffer );
	pBackBuffer->Release();
	if( FAILED( hr ) )
		//LOG FATAL ERROR
		exit(0);
}

void TE::Context::APIContext::CreateDepthStencilBufferAndView()
{
	// Create depth stencil texture buffer
	D3D11_TEXTURE2D_DESC descDepth;
	ZeroMemory( &descDepth, sizeof(descDepth) );
	descDepth.Width = GetWindowWidth();
	descDepth.Height = GetWindowHeight();
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	HRESULT hr = m_d3dDevice->CreateTexture2D( &descDepth, NULL, &m_d3dDepthStencilBuffer );
	if( FAILED( hr ) )
		//LOG FATAL ERROR
		exit(1);

	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory( &descDSV, sizeof(descDSV) );
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	hr = m_d3dDevice->CreateDepthStencilView( m_d3dDepthStencilBuffer, &descDSV, &m_d3dDepthStencilView );
	if( FAILED( hr ) )
		//LOG FATAL ERROR
		exit(1);

}

void TE::Context::APIContext::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC rs;
	ZeroMemory( &rs, sizeof(rs) );
	rs.FillMode = D3D11_FILL_SOLID;
	rs.CullMode = D3D11_CULL_BACK;
	rs.FrontCounterClockwise = false;
	rs.DepthBias = 0;
	rs.SlopeScaledDepthBias = 0.0f;
	rs.DepthBiasClamp = 0.0f;
	rs.DepthClipEnable = true;
	rs.ScissorEnable = false;
	rs.MultisampleEnable = false;
	rs.AntialiasedLineEnable = false;

	HRESULT hr = m_d3dDevice->CreateRasterizerState(&rs, &m_d3dRState);
	if( FAILED( hr ) )
		//LOG FATAL ERROR
		exit(1);
}

void TE::Context::APIContext::SetResolution( bool fullscreen, I32 width, I32 height, I32 colorBits, I32 positionX, I32 positionY )
{
	if (!m_initialized) return;

	if(fullscreen && width == 0 || height == 0)
	{	
		width = GetScreenWidth();
		height = GetScreenHeight();
	}

	PlatformWindow::SetResolution(fullscreen, width, height, colorBits, positionX, positionY);

	//Release buffers
	m_d3dBackBuffer->Release();
	m_d3dDepthStencilBuffer->Release();
	m_d3dDepthStencilView->Release();

	//Set new states
	//if(fullscreen) m_d3dSwapChain->SetFullscreenState(fullscreen, NULL);
	m_d3dSwapChain->ResizeBuffers(1, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, NULL);

	//re create buffers
	CreateBackBuffer();
	CreateDepthStencilBufferAndView();
	m_d3dDeviceContext->OMSetRenderTargets( 1, &m_d3dBackBuffer, m_d3dDepthStencilView);
}
