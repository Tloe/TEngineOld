#ifndef TEVERTEXBUFFERDX11_H
#define TEVERTEXBUFFERDX11_H

#include "TEDataTypes.h"
#include <memory>

struct ID3D11Buffer;

namespace TE {
    namespace Render {
        class Mesh;
    }
    namespace Context {
        class APIContext;
    }

    namespace Render {
        class APIVertexBuffer {
          public:
            APIVertexBuffer(Context::APIContext &apiContext, const Mesh &mesh);
            ~APIVertexBuffer();
            void Enable();
            void Disable();

            U32 IncreaseUsageCount();
            U32 DecreaseUsageCount();

          private:
            U32 m_usageCount;
            const Mesh &m_mesh;
            ID3D11Buffer *m_D3DvertexBuffer;
            Context::APIContext &m_apiContext;
        };

        typedef std::unique_ptr<APIVertexBuffer> APIVertexBufferUPtr;
    }
}

#endif
