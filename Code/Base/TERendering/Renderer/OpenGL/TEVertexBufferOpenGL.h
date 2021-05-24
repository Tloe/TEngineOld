#ifndef TEVERTEXBUFFEROPENGL_H
#define TEVERTEXBUFFEROPENGL_H

#include "TEDataTypes.h"
#include "TEOpenGL.h"

namespace TE::Render {
    class Mesh;
}
namespace TE::Render {
    class APIVertexBuffer {
      public:
        APIVertexBuffer(const Mesh &mesh);
        ~APIVertexBuffer();
        void Enable();
        void Disable();

        U32 IncreaseUsageCount();
        U32 DecreaseUsageCount();

      private:
        U32 m_usageCount;
        const Mesh &m_mesh;
        GLuint m_glVBO;
    };
}

#endif
