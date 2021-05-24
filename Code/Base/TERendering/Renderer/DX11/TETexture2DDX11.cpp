#include "Cg/cgD3D11.h"
#include <TEContextWinDX11.h>
#include <TETexture.h>
#include <TETexture2DDX11.h>
#include <d3d11.h>
#include <string>

TE::Render::APITexture2D::APITexture2D(Context::APIContext &context,
                                       Texture &texture,
                                       CGparameter cgParameter)
    : m_usageCount(1) {
    texture.Prepare();

    D3D11_SUBRESOURCE_DATA subData = {0};
    subData.pSysMem                = texture.GetImage().GetDataPtr();
    subData.SysMemPitch            = (texture.GetImage().GetDataSize() /
                           (texture.GetImage().GetWidth() * texture.GetImage().GetHeight())) *
                          texture.GetImage().GetWidth();

    D3D11_TEXTURE2D_DESC textureDesc = {0};
    textureDesc.Width                = texture.GetImage().GetWidth();
    textureDesc.Height               = texture.GetImage().GetHeight();
    textureDesc.Format               = DXGI_FORMAT_R8G8B8A8_UNORM;
    textureDesc.Usage                = D3D11_USAGE_DEFAULT;
    textureDesc.CPUAccessFlags       = 0;
    textureDesc.MiscFlags            = 0;
    textureDesc.MipLevels            = 1;
    textureDesc.ArraySize            = 1;
    textureDesc.SampleDesc.Count     = 1;
    textureDesc.SampleDesc.Quality   = 0;
    textureDesc.BindFlags            = D3D11_BIND_SHADER_RESOURCE;

    /*

    D3D11_IMAGE_INFO fileInfo;
    D3DX11GetImageInfoFromMemory( static_cast<const void*>(texture.GetImage().GetDataPtr()),
                                                              texture.GetImage().GetDataSize(),
                                                              NULL,
                                                              &fileInfo,
                                                              NULL );

    D3DX11_IMAGE_LOAD_INFO loadInfo;
    loadInfo.Width          = fileInfo.Width;
    loadInfo.Height         = fileInfo.Height;
    loadInfo.FirstMipLevel  = 0;
    loadInfo.MipLevels      = fileInfo.MipLevels;	//Set this in editor? Have TE types mapped
    to ogl and dx types loadInfo.Usage          = D3D11_USAGE_DEFAULT; loadInfo.BindFlags      =
    D3D11_BIND_SHADER_RESOURCE; loadInfo.CpuAccessFlags = 0; loadInfo.MiscFlags      = 0;
    loadInfo.Format         = fileInfo.Format;   //Map with textureInfo.colorType !
    loadInfo.Filter         = D3DX11_FILTER_NONE;
    loadInfo.MipFilter      = D3DX11_FILTER_NONE;
    loadInfo.pSrcInfo       = &fileInfo;

    HRESULT hr = D3DX11CreateTextureFromMemory(context.GetDevice(),
                                                                                       static_cast<const
    void*>(texture.GetImage().GetDataPtr()), texture.GetImage().GetDataSize(), &loadInfo, NULL,
                                                                                       &m_d3dTexture,
                                                                                       NULL);
    */

    HRESULT hr = context.GetDevice()->CreateTexture2D(&textureDesc, &subData, &m_d3dTexture);

    if (hr != S_OK)
        exit(1);

    // bind the texture to the cg texture parameter
    cgD3D11SetTextureParameter(cgParameter, m_d3dTexture);

    // initialize the state specified for a sampler parameter
    cgSetSamplerState(cgParameter);
}

TE::Render::APITexture2D::~APITexture2D() {}

void TE::Render::APITexture2D::Enable(CGparameter cgParameter) {
    cgD3D11SetTextureParameter(cgParameter, m_d3dTexture);
}

void TE::Render::APITexture2D::Disable() {}

U32 TE::Render::APITexture2D::IncreaseUsageCount() { return ++m_usageCount; }

U32 TE::Render::APITexture2D::DecreaseUsageCount() { return --m_usageCount; }
