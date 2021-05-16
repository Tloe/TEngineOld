#ifndef TEGRAPHICSTASK_H
#define TEGRAPHICSTASK_H

#include <TESystemTask.h>

namespace TE {
    namespace SceneGraph {
        class SceneManager;
    }

    namespace Graphics {
        class GraphicsTask : public Engine::SystemTask {
          public:
            GraphicsTask(SceneGraph::SceneManager &sceneManager);
            virtual void Run(); // Return bool until msvc bug is fixed
            virtual Bitmask GetTaskFlags();
            virtual void SetInterpolation(F32 interpolation);

          private:
            SceneGraph::SceneManager &m_sceneManager;
            F32 m_interpolation;
        };
    }
}

#endif
