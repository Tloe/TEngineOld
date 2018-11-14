#include <TEAPIResourceFactory.h>
#include "TEResource.h"
#include "TEEffect.h"
#include "TEBufferLayout.h"
#include "TEVertexBuffer.h"
#include "TEIndexBuffer.h"
#include "TETexture2D.h"
#include <assert.h>

#if TE_USE_DX11
#include <TEBufferLayoutDX11.h>
#include <TEContextWinDX11.h>
#include <TEIndexBufferDX11.h>
#include <TEMappingDX11.h>
#include <TETexture2DDX11.h>
#include <TEVertexBufferDX11.h>
#include "TEEffectDX11.h"

#elif TE_USE_OPENGL
#include <TEBufferLayoutOpenGL.h>
#include <TEContextWinOpenGL.h>
#include <TEIndexBufferOpenGL.h>
#include <TEMappingOpenGL.h>
#include <TETexture2DOpenGL.h>
#include <TEVertexBufferOpenGL.h>
#include "TEEffectOpenGL.h"
#endif



TE::Render::APIResourceFactory::APIResourceFactory(APIContext& apiContext, CGcontext& cgContext)
	:
	m_apiContext(apiContext),
	m_cgContext(cgContext)
{

}

TE::Render::APIResourceFactory::~APIResourceFactory()
{

}

void TE::Render::APIResourceFactory::SetupResource( const Effect& effect )
{

}

void TE::Render::APIResourceFactory::SetupResource( const BufferLayout& bufferLayout, const Effect& effect )

}

void TE::Render::APIResourceFactory::SetupResource( const VertexBuffer& vertexBuffer )
{

}

void TE::Render::APIResourceFactory::SetupResource( const IndexBuffer& indexBuffer )
{

}

void TE::Render::APIResourceFactory::SetupResource( const Texture2D& texture2D )
{
	ResourceMap::iterator findItr = m_resources.find(&texture2D);
	if (findItr == m_resources.end())
	{
		m_resources.insert(std::make_pair(&texture2D, new APITexture2D(m_apiContext, texture2D)));
	}
}

void TE::Render::APIResourceFactory::EnableResource( Resources::Resource* resource )
{
	assert(m_resources.find(resource) != m_resources.end() && "Resource not found.");
	m_resources[resource]->Enable(m_apiContext);
}

void TE::Render::APIResourceFactory::DisableResource( Resources::Resource* resource )
{
	assert(m_resources.find(resource) != m_resources.end() && "Resource not found.");
	m_resources[resource]->Disable(m_apiContext);
}

TE::Render::APIEffectPtr& TE::Render::APIResourceFactory::GetAPIEffect( const Effect& effect )
{
	EffectMap::iterator findItr = m_effects.find(&effect);
	assert(findItr != m_effects.end());
	
	return findItr->second;
}
