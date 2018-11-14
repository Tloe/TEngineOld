#include "TERenderer.h"
#include "TEApiRendererIncludes.h"
#include "TEApiResourcesIncludes.h"
#include <TEMatrix4D.h>
#include <TETexture.h>
#include <TEEffect.h>

#include <algorithm>
#include <assert.h>
#include <list>

void TECgErrorHandler(CGcontext cgContext, CGerror error, void *data)
{
    std::cout << "CG ERROR - string: " << std::endl;
    std::cout << cgGetErrorString(error) << std::endl;
	if (cgContext)
	{
        std::cout << "CG ERROR - last listing:" << cgGetLastListing(cgContext) << std::endl;
	}
        assert(false);
}

TE::Render::Renderer::Renderer(TE::Platform::OSWinId osWinId, IO::FileIO& fileIO )
    : m_apiRenderer(osWinId, fileIO)
    , m_meshManager(fileIO)
    , m_effectManager(fileIO)
    , m_textureManager(fileIO)
    , m_clearColor(Math::Base<Real>::REAL_ZERO, static_cast<Real>(0.125), static_cast<Real>(0.3), Math::Base<Real>::REAL_ONE)
    , m_viewProjectionMatrix("viewProjection")
    , m_modelMatrix("world")
{

}

TE::Render::Renderer::Renderer(TE::IO::FileIO &fileIO)
    : m_apiRenderer(fileIO)
    , m_meshManager(fileIO)
    , m_effectManager(fileIO)
    , m_textureManager(fileIO)
    , m_clearColor(Math::Base<Real>::REAL_ZERO, static_cast<Real>(0.125), static_cast<Real>(0.3), Math::Base<Real>::REAL_ONE)
    , m_viewProjectionMatrix("viewProjection")
    , m_modelMatrix("world")
{
}

TE::Render::Renderer::~Renderer()
{

}

void TE::Render::Renderer::Startup()
{
    cgSetErrorHandler(TECgErrorHandler, nullptr);
	m_cgContext = cgCreateContext();

    m_apiRenderer.Initialize(m_cgContext);
}

void TE::Render::Renderer::Shutdown()
{
    m_apiRenderer.Cleanup();

	cgDestroyContext(m_cgContext);
}

void TE::Render::Renderer::BeginFrame()
{
	m_apiRenderer.BeginFrame(m_clearColor);
}

void TE::Render::Renderer::EndFrame()
{
	m_apiRenderer.EndFrame();
}

void TE::Render::Renderer::InitEffect( Effect& effect )
{
	effect.Initialize(m_cgContext);    
}

void TE::Render::Renderer::InitAPIMesh( const Mesh& mesh, const Effect& effect )
{
    if (m_apiVertexBufferLayouts.find(&mesh) == m_apiVertexBufferLayouts.end())
	{
        assert(m_apiVertexBuffers.find(&mesh) == m_apiVertexBuffers.end() && "VertexBuffer allready loaded");
        assert(m_apiIndexBuffers.find(&mesh) == m_apiIndexBuffers.end() && "IndexBuffer allready loaded");

        APIVertexBufferUPtr apiVertexBufferLayout = m_apiRenderer.CreateAPIVertexBuffer(mesh);
        m_apiVertexBuffers.insert(std::make_pair(&mesh, std::move(apiVertexBufferLayout)));

        m_apiVertexBuffers.find(&mesh)->second->Enable();
        APIVertexBufferLayoutUPtr apiBufferLayout = m_apiRenderer.CreateAPIVertexBufferLayout(mesh, effect);
        m_apiVertexBuffers.find(&mesh)->second->Disable();
        m_apiVertexBufferLayouts.insert(std::make_pair(&mesh, std::move(apiBufferLayout)));

        APIIndexBufferUPtr apiIndexBuffer = m_apiRenderer.CreateAPIIndexBuffer(mesh);
        m_apiIndexBuffers.insert(std::make_pair(&mesh, std::move(apiIndexBuffer)));
	}
    else
    {
        m_apiVertexBufferLayouts.find(&mesh)->second->IncreaseUsageCount();
        m_apiVertexBuffers.find(&mesh)->second->IncreaseUsageCount();
        m_apiIndexBuffers.find(&mesh)->second->IncreaseUsageCount();
    }
}

void TE::Render::Renderer::InitAPITexture( Texture& texture, Effect& effect )
{
    APITextureMap::iterator findItr = m_apiTextures.find(&texture);
	if (findItr == m_apiTextures.end())
	{
        APITexture2DUPtr apiTexture2D = m_apiRenderer.CreateAPITexture2D(texture, effect);
        m_apiTextures.insert(std::make_pair(&texture, std::move(apiTexture2D)));
    }
    else
    {
        m_apiTextures.find(&texture)->second->IncreaseUsageCount();
    }
}

void TE::Render::Renderer::CleanupAPIMesh( const Mesh& mesh )
{
    if(m_apiVertexBufferLayouts.find(&mesh)->second->DecreaseUsageCount() == 0)
        m_apiVertexBufferLayouts.erase(&mesh);

    if(m_apiVertexBuffers.find(&mesh)->second->DecreaseUsageCount() == 0)
        m_apiVertexBuffers.erase(&mesh);

    if(m_apiIndexBuffers.find(&mesh)->second->DecreaseUsageCount() == 0)
        m_apiIndexBuffers.erase(&mesh);
}

void TE::Render::Renderer::CleanupAPITexture( const Texture& texture )
{
    DisableAPITexture(texture);
    if(m_apiTextures.find(&texture)->second->DecreaseUsageCount() == 0)
        m_apiTextures.erase(&texture);
}

void TE::Render::Renderer::CleanupEffect( Effect& effect )
{
	effect.Cleanup();
}

void TE::Render::Renderer::EnableAPIMesh( const Mesh& mesh )
{
    m_apiVertexBufferLayouts.find(&mesh)->second->Enable();
    m_apiVertexBuffers.find(&mesh)->second->Enable();
    m_apiIndexBuffers.find(&mesh)->second->Enable();
}

void TE::Render::Renderer::EnableAPITexture( const Texture& texture, Effect& effect )
{
    m_apiTextures.find(&texture)->second->Enable(effect.GetCGParamaeter("texSampler0"));
}

void TE::Render::Renderer::SetClearColor( const ColorRGBA& clearColor )
{
	m_clearColor = clearColor;
}

void TE::Render::Renderer::DisableAPIMesh( const Mesh& mesh )
{
    m_apiVertexBuffers.find(&mesh)->second->Disable();
    m_apiVertexBufferLayouts.find(&mesh)->second->Disable();
    m_apiIndexBuffers.find(&mesh)->second->Disable();
}

void TE::Render::Renderer::DisableAPITexture( const Texture& texture )
{
    m_apiTextures.find(&texture)->second->Disable();
}

void TE::Render::Renderer::SetViewProjectionMatrix( const Math::Matrix4D<Real>& viewProjection, Effect& effect )
{
    m_viewProjectionMatrix.Update(effect.GetCGParamaeter("viewProjection"), viewProjection);
}

void TE::Render::Renderer::SetModelMatrix( const Math::Matrix4D<Real>& model, Effect& effect )
{
    m_modelMatrix.Update(effect.GetCGParamaeter("world"), model);
}

bool TE::Render::Renderer::SetNextPass( Effect& effect )
{
	return effect.SetupNextPass();
}

void TE::Render::Renderer::Draw( I32 indexCount )
{
	m_apiRenderer.Draw(indexCount);
}

void TE::Render::Renderer::SetWindowed(I32 width, I32 height, I32 viewportWidth, I32 viewportHeight, bool updateViewport , I32 positionX, I32 positionY)
{
	bool fullscreen = false;
    m_apiRenderer.SetResolution(width, height, viewportWidth, viewportHeight,fullscreen, updateViewport, positionX, positionY);
}

void TE::Render::Renderer::SetFullscreen( I32 width, I32 height, bool updateViewport )
{
	bool fullscreen = true;
    m_apiRenderer.SetResolution(width, height, width, height,fullscreen, updateViewport, -1, -1);
}

TE::Resources::ResourceHandle<TE::Render::Mesh> TE::Render::Renderer::GetMeshHandle( const std::string& filePath, bool lazyLoad /*= false*/ )
{
	if (!m_meshManager.IsRegistered(filePath))
	{
		Mesh newMesh(filePath);
		return m_meshManager.AddResource(newMesh, lazyLoad);
	}
	return m_meshManager.GetResourceHandle(filePath);
}

TE::Resources::ResourceHandle<TE::Render::Texture> TE::Render::Renderer::GetTextureHandle( const std::string& filePath, bool lazyLoad /*= false*/ )
{
	if (!m_textureManager.IsRegistered(filePath))
	{
		Texture newTexture(filePath);
		return m_textureManager.AddResource(newTexture, lazyLoad);
	}
	return m_textureManager.GetResourceHandle(filePath);
}

TE::Resources::ResourceHandle<TE::Render::Effect> TE::Render::Renderer::GetEffectHandle( const std::string& filePath, bool lazyLoad /*= false*/ )
{
	if (!m_effectManager.IsRegistered(filePath))
	{
        Effect newEffect(filePath);
        return m_effectManager.AddResource(newEffect, lazyLoad);
	}
    return m_effectManager.GetResourceHandle(filePath);
}

TE::Platform::PlatformWindow &TE::Render::Renderer::GetPlatformWindow()
{
    return m_apiRenderer.GetPlatformWindow();
}
