#ifndef TEGLOBALSTATE_H
#define TEGLOBALSTATE_H

#include "TEDataTypes.h"
#include <memory>

namespace TE {
namespace SceneGraph {
    struct GlobalState {
      public:
        virtual ~GlobalState();

        enum {
            STATE_ALPHA,
            STATE_CULL,
            // STATE_DITHER,
            STATE_FOG,
            STATE_MATERIAL,
            // STATE_SHADE,
            STATE_WIREFRAME,
            STATE_ZBUFFER,
            STATE_COUNT
        };

        virtual I32 GetGlobalStateType() const = 0;

        static std::unique_ptr<TE::SceneGraph::GlobalState> s_default[STATE_COUNT];

      protected:
        GlobalState() {
        }
    };
}
}

#endif
