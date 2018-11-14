/*#include <TEDefines.h>

#if TEWINDOWS

#include <TEWindowWinDx.h>

TE::Render::WindowWinDx::WindowWinDx( HINSTANCE &hInstance, int nCmdShow, const WindowInf& winInf ) : Window(winInf), m_featureLevel(D3D_FEATURE_LEVEL_11_0), m_pd3dDevice(NULL), m_pImmediateContext(NULL), m_pSwapChain(NULL), m_pRenderTargetView(NULL)
{
	m_nCmdShow = nCmdShow;
	m_hInstance = hInstance;
}

TE::Render::WindowWinDx::~WindowWinDx()
{
	DestroyWindow(m_hWnd);
}

bool TE::Render::WindowWinDx::Initialize()
{
	return InitWindow() && InitContext();
}

bool TE::Render::WindowWinDx::DeInitialize()
{
	if( m_pImmediateContext ) m_pImmediateContext->ClearState();

	if( m_pRenderTargetView ) m_pRenderTargetView->Release();
	if(	m_pSwapChain ) m_pSwapChain->Release();
	if( m_pImmediateContext ) m_pImmediateContext->Release();
	if( m_pd3dDevice ) m_pd3dDevice->Release();

	return true;
}

void TE::Render::WindowWinDx::NextFrame()
{
	m_pSwapChain->Present( 0, 0 );
}

bool TE::Render::WindowWinDx::InitWindow()
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof( WNDCLASSEX );
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
	wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = GetWindowInfo().name.c_str();
	wcex.hIconSm = NULL;

	if(!RegisterClassEx (&wcex))
		//Log
		return false;

	RECT rc =
	{
		GetWindowInfo().posX, GetWindowInfo().posY,
		GetWindowInfo().posX + GetWindowInfo().width,
		GetWindowInfo().posY + GetWindowInfo().height
	};

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	m_hWnd = CreateWindow(
		GetWindowInfo().name.c_str(), GetWindowInfo().name.c_str(),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		rc.right - rc.left, rc.bottom - rc.top,
		NULL, NULL, m_hInstance, NULL );

	if (!m_hWnd)
		//Log
		return false;

	ShowWindow(m_hWnd, m_nCmdShow);

	return true;
}

bool TE::Render::WindowWinDx::InitContext()
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
	ZeroMemory( &sd, sizeof( sd ) );
	sd.BufferCount = 1;
	sd.BufferDesc.Width = GetWindowInfo().width;
	sd.BufferDesc.Height = GetWindowInfo().height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = m_hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	D3D_DRIVER_TYPE driverType;
	for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ )
	{
		driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain( NULL, driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &m_pSwapChain, &m_pd3dDevice, &m_featureLevel, &m_pImmediateContext );
		if( SUCCEEDED( hr ) )
			break;
	}
	if( FAILED( hr ) )
		return false;

	// Create a render target view
	ID3D11Texture2D* pBackBuffer = NULL;
	hr = m_pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer );
	if( FAILED( hr ) )
		return false;

	hr = m_pd3dDevice->CreateRenderTargetView( pBackBuffer, NULL, &m_pRenderTargetView );
	pBackBuffer->Release();
	if( FAILED( hr ) )
		return false;

	m_pImmediateContext->OMSetRenderTargets( 1, &m_pRenderTargetView, NULL );

	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = static_cast<float>(GetWindowInfo().width);
	vp.Height = static_cast<float>(GetWindowInfo().height);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_pImmediateContext->RSSetViewports( 1, &vp );

	return true;
}

void TE::Render::WindowWinDx::TestDrawFunc()
{
	float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; //red,green,blue,alpha
	m_pImmediateContext->ClearRenderTargetView( m_pRenderTargetView, ClearColor );

	NextFrame();
}

LRESULT CALLBACK TE::Render::WindowWinDx::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch( message )
	{
	case WM_PAINT:
		hdc = BeginPaint( hWnd, &ps );
		EndPaint( hWnd, &ps );
		break;

	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;

	default:
		return DefWindowProc( hWnd, message, wParam, lParam );
	}

	return 0;
}

#endif

*/