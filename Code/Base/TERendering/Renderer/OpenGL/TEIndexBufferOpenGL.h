#ifndef TEINDEXBUFFEROPENGL_H
#define TEINDEXBUFFEROPENGL_H

#include "TEDataTypes.h"
#include "TEOpenGL.h"

namespace TE::Render {
  class Mesh;

  class APIIndexBuffer {
  public:
    APIIndexBuffer(const Mesh &mesh);
    ~APIIndexBuffer();

    void Enable();
    void Disable();

    U32 IncreaseUsageCount();
    U32 DecreaseUsageCount();

  private:
    U32 m_usageCount;
    const Mesh &m_mesh;
    GLuint m_glIBO;
  };
}

#endif
