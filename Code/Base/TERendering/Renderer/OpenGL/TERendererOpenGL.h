#ifndef TERENDEREROPENGL_H
#define TERENDEREROPENGL_H

#include "TEApiContextIncludes.h"
#include "TEDataTypes.h"
#include "TEPlatformWindowIncludes.h"

#include <memory>
#include <thread>

namespace TE {
    class ColorRGBA;
}

namespace TE::IO {
    class FileIO;
}

namespace TE::Platform {
    class PlatformWindow;
}

namespace TE::Render {
    class Effect;
    class Mesh;
    class Texture;

    class APIVertexBufferLayout;
    using APIVertexBufferLayoutUPtr = std::unique_ptr<APIVertexBufferLayout>;

    class APIVertexBuffer;
    using APIVertexBufferUPtr = std::unique_ptr<APIVertexBuffer>;

    class APIIndexBuffer;
    using APIIndexBufferUPtr = std::unique_ptr<APIIndexBuffer>;

    class APITexture2D;
    using APITexture2DUPtr = std::unique_ptr<APITexture2D>;
}

namespace TE::Context {
    class APIContext;
}
namespace TE::Render {
    class APIRenderer {
      public:
        APIRenderer(Platform::OSWinId osWinId, IO::FileIO &fileIO);
        APIRenderer(IO::FileIO &fileIO);
        ~APIRenderer();

        void Initialize(/*CGcontext& cgContext*/);
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

        void BeginFrame(const ColorRGBA &clearColor);
        void EndFrame();
        void Draw(I32 indexCount);

        APIVertexBufferLayoutUPtr CreateAPIVertexBufferLayout(const Mesh &mesh,
                                                              const Effect &effect);
        APIVertexBufferUPtr CreateAPIVertexBuffer(const Mesh &mesh);
        APIIndexBufferUPtr CreateAPIIndexBuffer(const Mesh &mesh);
        APITexture2DUPtr CreateAPITexture2D(Texture &texture, Effect &effect);

        Platform::PlatformWindow &GetPlatformWindow();

      private:
        std::thread::id m_threadId;
        Context::APIContext m_apiContext;
    };
}

#endif
