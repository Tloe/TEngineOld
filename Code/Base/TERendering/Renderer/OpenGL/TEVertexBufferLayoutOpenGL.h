#ifndef TEBUFFERLAYOUTOPENGL_H
#define TEBUFFERLAYOUTOPENGL_H

#include "TEDataTypes.h"

#include "TEOpenGL.h"
#include "TERendererOpenGL.h"

#include <memory>
#include <vector>

namespace TE::Render {
  class Effect;
  class Mesh;

  class APIVertexBufferLayout {
  public:
    APIVertexBufferLayout(const Render::Mesh &mesh, const Render::Effect &effect);
    ~APIVertexBufferLayout();

    void Enable();
    void Disable();

    U32 IncreaseUsageCount();
    U32 DecreaseUsageCount();

  private:
    U32 m_usageCount;

    I32 m_stride;

    bool m_hasPosition;
    I32 m_positionValueCount;
    GLuint m_positionValueType;
    I32 m_positionOffset;

    bool m_hasNormals;
    I32 m_normalValueCount;
    GLuint m_normalValueType;
    I32 m_normalOffset;

    unsigned m_textureCount;
    std::vector<I32> m_textureValueCount;
    std::vector<GLuint> m_textureValueType;
    std::vector<I32> m_textureOffset;

    GLuint m_glVAO;
  };

  using APIVertexBufferLayoutUPtr = std::unique_ptr<APIVertexBufferLayout>;
}

#endif
