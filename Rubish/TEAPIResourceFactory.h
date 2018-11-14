#ifndef TEAPIRESOURCEFACTORY_H
#define TEAPIRESOURCEFACTORY_H

#include <memory>
#include <unordered_map>
#include <Cg/cg.h>

namespace TE
{
	//Forward declarations
	namespace Render { struct APIContext; }
	namespace Render { class Effect; typedef std::shared_ptr<Effect> EffectPtr; }
	namespace Render { class BufferLayout; typedef std::shared_ptr<BufferLayout> BufferLayoutPtr; }
	namespace Render { class VertexBuffer; typedef std::shared_ptr<VertexBuffer> VertexBufferPtr; }
	namespace Render { class IndexBuffer; typedef std::shared_ptr<IndexBuffer> IndexBufferPtr; }
	namespace Render { class Texture2D; typedef std::shared_ptr<Texture2D> Texture2DPtr; }
	namespace Render { class APIResource; typedef std::shared_ptr<APIResource> APIResourcePtr; }
	namespace Render { class APIEffect; typedef std::shared_ptr<APIEffect> APIEffectPtr; }
	namespace Resources { class Resource; }
	//End forward declarations

	namespace Render
	{
		class APIResourceFactory
		{
		public:
			APIResourceFactory(APIContext& apiContext, CGcontext& cgContext);
			~APIResourceFactory();

			void SetupResource(const Effect& effect);
			void SetupResource(const BufferLayout& bufferLayout, const Effect& effect);
			void SetupResource(const VertexBuffer& vertexBuffer);
			void SetupResource(const IndexBuffer& indexBuffer);
			void SetupResource(const Texture2D& texture2D);

			void EnableResource(Resources::Resource* resource);
			void DisableResource(Resources::Resource* resource);

			APIEffectPtr& GetAPIEffect(const Effect& effect);
		private:
			ResourceMap m_resources;
			EffectMap m_effects;
			APIContext& m_apiContext;
			CGcontext& m_cgContext;
		};
	}
}

#endif