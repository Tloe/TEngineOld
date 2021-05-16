#ifndef TESYSTEMTASK_H
#define TESYSTEMTASK_H

#include "TEDataTypes.h"

#include <vector>

namespace TE {
namespace Engine {
    namespace TaskFlags {
        enum {
            NotSet          = 0,
            RunInMainThread = (1 << 0),
            DrawingTask     = (1 << 1)
        };
    }

    class SystemTask {
      public:
        virtual ~SystemTask();
        virtual void Run()             = 0;
        virtual Bitmask GetTaskFlags() = 0;
        virtual void SetInterpolation(F32 interpolation) {}
        virtual void SetDeltaValues(U64 t, U64 dt) {}
    };
}
}

#endif
