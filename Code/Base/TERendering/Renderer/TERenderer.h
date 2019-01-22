#ifndef TERENDERER_H
#define TERENDERER_H

#include "TEDataTypes.h"
#include "TEApiRendererIncludes.h"
#include "TEPlatformWindowIncludes.h"
#include "TEMatrix4D.h"
#include "TEShaderParameter.h"
#include "TEColor.h"
#include "TEResourceManager.h"
#include "TEResource.h"
#include "TEEffect.h"
#include "TETexture.h"
#include "TEResourceHandle.h"
#include "TEMesh.h"

#include <string>
#include <set>
#include <functional>
#include <unordered_map>

namespace TE
{
	namespace Render { class APIVertexBufferLayout; typedef std::unique_ptr<APIVertexBufferLayout> APIVertexBufferLayoutUPtr; }
	namespace Render { class APIVertexBuffer; typedef std::unique_ptr<APIVertexBuffer> APIVertexBufferUPtr; }
	namespace Render { class APIIndexBuffer; typedef std::unique_ptr<APIIndexBuffer> APIIndexBufferUPtr; }
	namespace Render { class APITexture2D; typedef std::unique_ptr<APITexture2D> APITexture2DUPtr; }

	namespace Render { class Effect; }
	
    namespace Context { class APIContext; }

	namespace IO { class FileIO; }
	
	namespace Render
	{
        class Renderer
		{
		public:
            Renderer(Platform::OSWinId osWinId, IO::FileIO& fileIO);
            Renderer(IO::FileIO& fileIO);
			~Renderer();

			void Startup();
			void Shutdown();

			void BeginFrame();
			void EndFrame();

			void Draw(I32 indexCount);

            void SetWindowed(I32 width,
                             I32 height,
                             I32 viewportWidth,
                             I32 viewportHeight,
                             bool updateViewport,
                             I32 positionX,
                             I32 positionY);
            void SetFullscreen(I32 width,
                               I32 height,
                               bool updateViewport);

			void SetClearColor(const ColorRGBA& clearColor);
			void SetViewProjectionMatrix(const Math::Matrix4D<Real>& viewProjection, Effect& effect);
			void SetModelMatrix(const Math::Matrix4D<Real>& model, Effect& effect);
			bool SetNextPass(Effect& effect);
			
			void InitEffect(Effect& effect);
            void InitAPIMesh(const Mesh& mesh, const Effect& effect);
            void InitAPITexture(Texture& texture, Effect& effect);
						
			void CleanupEffect(Effect& effect);
            void CleanupAPIMesh(const Mesh& mesh);
            void CleanupAPITexture(const Texture& texture);

            void EnableAPIMesh(const Mesh& mesh);
            void EnableAPITexture(const Texture& texture, Effect& effect);

            void DisableAPIMesh(const Mesh& mesh);
            void DisableAPITexture(const Texture& texture);

            Resources::ResourceHandle<Mesh> GetMeshHandle(const std::string& filePath, bool lazyLoad = false);
            Resources::ResourceHandle<Texture> GetTextureHandle(const std::string& filePath, bool lazyLoad = false);
            Resources::ResourceHandle<Effect> GetEffectHandle(const std::string& filePath, bool lazyLoad = false);

            Platform::PlatformWindow & GetPlatformWindow();
		private:
            typedef std::unordered_map<const Mesh*, APIVertexBufferLayoutUPtr> APIVertexBufferLayoutMap;
            typedef std::unordered_map<const Mesh*, APIVertexBufferUPtr> APIVertexBufferMap;
            typedef std::unordered_map<const Mesh*, APIIndexBufferUPtr> APIIndexBufferMap;
            typedef std::unordered_map<const Texture*, APITexture2DUPtr> APITextureMap;

            APIRenderer m_apiRenderer;

			APIVertexBufferLayoutMap m_apiVertexBufferLayouts;
			APIVertexBufferMap m_apiVertexBuffers;
			APIIndexBufferMap m_apiIndexBuffers;
			APITextureMap m_apiTextures;
			
			Resources::ResourceManager<Render::Mesh> m_meshManager;
            Resources::ResourceManager<Render::Effect> m_effectManager;
			Resources::ResourceManager<Render::Texture> m_textureManager;

            ColorRGBA m_clearColor;

            ShaderParameter<Math::Matrix4D<Real> > m_viewProjectionMatrix;
            ShaderParameter<Math::Matrix4D<Real> > m_modelMatrix;

			/* CGcontext m_cgContext; */
		};
	}
}

#endif
