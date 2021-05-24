#ifndef TEVERTEXBUFFERDX11_H
#define TEVERTEXBUFFERDX11_H

#include "TEDataTypes.h"
#include "TERendererOpenGL.h"
#include <memory>

struct ID3D11Buffer;

namespace TE::Context {
  class APIContext;
}

namespace TE::Render {
  class Mesh;

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

  using APIVertexBufferUPtr = std::unique_ptr<APIVertexBuffer>;
}

#endif
