#ifndef TETIME_H
#define TETIME_H

#include "TEDataTypes.h"

namespace TE {
namespace Time {
    enum class Units {
        Milliseconds,
        Microseconds,
        Nanoseconds
    };

    namespace Millisecond {
        enum {
            Second     = 1000,
            HalfSecond = 500
        };
    }

    namespace Microseconds {
        enum {
            Second     = 1000000,
            HalfSecond = 500000
        };
    }

    namespace Nanoseconds {
        enum {
            Second     = 1000000000,
            HalfSecond = 500000000
        };
    }
}
}

#endif