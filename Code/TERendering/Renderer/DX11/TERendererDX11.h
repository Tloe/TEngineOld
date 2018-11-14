#ifndef TERENDERERDX11_H
#define TERENDERERDX11_H

#include "TEDataTypes.h"

#include <Cg/cg.h>

#include <memory>

namespace TE
{
	class ColorRGBA;

	namespace Render { class Effect; }
	namespace Render { class Mesh; }
	namespace Render { class Texture; }

	namespace Render { class APIVertexBufferLayout; typedef std::unique_ptr<APIVertexBufferLayout> APIVertexBufferLayoutUPtr; }
	namespace Render { class APIVertexBuffer; typedef std::unique_ptr<APIVertexBuffer> APIVertexBufferUPtr; }
	namespace Render { class APIIndexBuffer; typedef std::unique_ptr<APIIndexBuffer> APIIndexBufferUPtr; }
	namespace Render { class APITexture2D; typedef std::unique_ptr<APITexture2D> APITexture2DUPtr; }

	namespace Context { class APIContext; }

	namespace Render
	{
		class APIRenderer
		{
		public:
			APIRenderer(Context::APIContext& apiContext);
			~APIRenderer();

            void Initialize(CGcontext& cgContext);
            void Cleanup();

			void SetResolution(I32 width,
							   I32 height,
							   I32 viewportWidth,
							   I32 viewportHeight,
							   bool fullscreen,
							   bool updateViewport,
							   I32 positionX,
							   I32 positionY);
			void SetViewPort(I32 x, I32 y, I32 width, I32 height);

			void BeginFrame(const ColorRGBA& clearColor);
			void EndFrame();
			void Draw(I32 indexCount);

			APIVertexBufferLayoutUPtr CreateAPIVertexBufferLayout(const Mesh& mesh, const Effect& effect);
			APIVertexBufferUPtr CreateAPIVertexBuffer(const Mesh& mesh);
			APIIndexBufferUPtr CreateAPIIndexBuffer(const Mesh& mesh);
			APITexture2DUPtr CreateAPITexture2D(Texture& texture, Effect& effect);

		private:
			Context::APIContext& m_apiContext;
		};
	}
}

#endif
