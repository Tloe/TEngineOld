#ifndef TEVERTEXBUFFERLAYOUTDX11_H
#define TEVERTEXBUFFERLAYOUTDX11_H

#include "TEDataTypes.h"
#include "TERendererOpenGL.h"

#include <memory>

struct ID3D11InputLayout;

namespace TE::Context {
  class APIContext;
}

namespace TE::Render {
  class Effect;
  class Mesh;

  class APIVertexBufferLayout {
  public:
    APIVertexBufferLayout(Context::APIContext &apiContext,
                          const Render::Mesh &mesh,
                          const Render::Effect &effect);
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

  using APIVertexBufferLayoutUPtr = std::unique_ptr<APIVertexBufferLayout>;
}

#endif
