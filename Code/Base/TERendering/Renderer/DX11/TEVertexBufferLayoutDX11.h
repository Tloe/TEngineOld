#ifndef TEVERTEXBUFFERLAYOUTDX11_H
#define TEVERTEXBUFFERLAYOUTDX11_H

#include "TEDataTypes.h"

#include <memory>

struct ID3D11InputLayout;

namespace TE {
    namespace Context {
        class APIContext;
    }
    namespace Render {
        class Effect;
    }
    namespace Render {
        class Mesh;
    }

    namespace Render {
        class APIVertexBufferLayout {
          public:
            APIVertexBufferLayout(Context::APIContext &apiContext, const Render::Mesh &mesh, const Render::Effect &effect);
            ~APIVertexBufferLayout();

            void Enable();
            void Disable();

            U32 IncreaseUsageCount();
            U32 DecreaseUsageCount();

          private:
            U32 m_usageCount;
            ID3D11InputLayout *m_D3D11layout;
            Context::APIContext &m_apiContext;
        };

        typedef std::unique_ptr<APIVertexBufferLayout> APIVertexBufferLayoutUPtr;
    }
}

#endif
