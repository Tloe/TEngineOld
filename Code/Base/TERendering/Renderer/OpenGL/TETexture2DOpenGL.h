#ifndef TETEXTURE2DOPENGL_H
#define TETEXTURE2DOPENGL_H

#include "TEDataTypes.h"

#include "TEOpenGL.h"

/* #include "Cg/cg.h" */

namespace TE {
    namespace Render {
        class Texture;
    }

    namespace Render {
        class APITexture2D {
          public:
            APITexture2D(Texture &texture /*, CGparameter cgParameter */);
            ~APITexture2D();
            void Enable(/*CGparameter cgParameter*/);
            void Disable();

            U32 IncreaseUsageCount();
            U32 DecreaseUsageCount();

          private:
            U32 m_usageCount;
            GLuint m_glTexture;
        };
    }
}

#endif
