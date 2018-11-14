#include <TEWindowWinDX11.h>
#include <TEColor.h>
#include <TEContextWinDX11.h>
#include <TEMathBase.h>

TE::Context::APIPlatformWindow::APIPlatformWindow()
{
}

TE::Context::APIPlatformWindow::~APIPlatformWindow()
{
}

void TE::Context::APIPlatformWindow::Init(TE::Render::APIContext& apiContext, TE::Context::Window& window)
{
	HRESULT hr = S_OK;

	unsigned createDeviceFlags = 0;
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
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	unsigned numFeatureLevels = ARRAYSIZE( featureLevels );

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory( &sd, sizeof( DXGI_SWAP_CHAIN_DESC ) );
	sd.BufferCount = 1;
	sd.BufferDesc.Width = GetWindowRef().GetWidth();
	sd.BufferDesc.Height = GetWindowRef().GetHeight();
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = GetHWND();
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	//sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	D3D_DRIVER_TYPE driverType;
	for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ )
	{
		driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain( NULL, driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &apiContext.swapChain, &apiContext.device, &apiContext.featureLevel, &apiContext.devcontext );
		if( SUCCEEDED( hr ) )
			break;
	}
	if( FAILED( hr ) )
		//LOG FATAL ERROR
		exit(0);

	// Create a render target view
	ID3D11Texture2D* pBackBuffer = NULL;
	hr = apiContext.swapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer );
	if( FAILED( hr ) )
		//LOG FATAL ERROR
		exit(0);

	hr = apiContext.device->CreateRenderTargetView( pBackBuffer, NULL, &apiContext.backBuffer );
	pBackBuffer->Release();
	if( FAILED( hr ) )
		//LOG FATAL ERROR
		exit(0);

	// Create depth stencil texture
	D3D11_TEXTURE2D_DESC descDepth;
	ZeroMemory( &descDepth, sizeof(descDepth) );
	descDepth.Width = GetWindowRef().GetWidth();
	descDepth.Height = GetWindowRef().GetHeight();
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	hr = apiContext.device->CreateTexture2D( &descDepth, NULL, &apiContext.pDepthStencilBuffer );
	if( FAILED( hr ) )
		//LOG FATAL ERROR
		exit(1);

	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory( &descDSV, sizeof(descDSV) );
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	hr = apiContext.device->CreateDepthStencilView( apiContext.pDepthStencilBuffer, &descDSV, &apiContext.pDepthStencilView );
	if( FAILED( hr ) )
		//LOG FATAL ERROR
		exit(1);

	apiContext.devcontext->OMSetRenderTargets( 1, &apiContext.backBuffer, apiContext.pDepthStencilView);

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
	
	hr = apiContext.device->CreateRasterizerState(&rs, &apiContext.pRState);
	if( FAILED( hr ) )
		//LOG FATAL ERROR
		exit(1);

	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = static_cast<Real>(GetWindowRef().GetWidth());
	vp.Height = static_cast<Real>(GetWindowRef().GetHeight());
	vp.MinDepth = Math::Base<Real>::REAL_ZERO;
	vp.MaxDepth = Math::Base<Real>::REAL_ONE;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	apiContext.devcontext->RSSetViewports( 1, &vp );
}

void TE::Context::APIPlatformWindow::Cleanup(TE::Render::APIContext& apiContext)
{
	WindowWin::Cleanup();

	//if(	m_context.m_pSwapChain ) m_context.m_pSwapChain->SetFullscreenState(FALSE, NULL);

	if( apiContext.devcontext ) apiContext.devcontext->ClearState();

	if( apiContext.backBuffer ) apiContext.backBuffer->Release();
	if(	apiContext.swapChain ) apiContext.swapChain->Release();
	if( apiContext.devcontext ) apiContext.devcontext->Release();
	if( apiContext.device ) apiContext.device->Release();
}

void TE::Context::APIPlatformWindow::BeginFrame()
{
	WindowWin::BeginFrame();
}

void TE::Context::APIPlatformWindow::EndFrame()
{
}
