#ifndef TEPOTENTIALCONTACT_H
#define TEPOTENTIALCONTACT_H

#include "TEDataTypes.h"

namespace TE::CollisionDetection {
    struct PotentialContact {
        I32 entityId0;
        I32 entityId1;
    };
}

#endif
