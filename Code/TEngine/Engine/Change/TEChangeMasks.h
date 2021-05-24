#ifndef TESYSTEMTYPES_H
#define TESYSTEMTYPES_H

#include "TEDataTypes.h"

#include <assert.h>
#include <string>

namespace TE::Engine::Change {
  const Bitmask64 NotSet = 0;

  namespace Scene {
    const Bitmask64 CreateObject = (1 << 0);
    const Bitmask64 DeleteObject = (1 << 1);
    const Bitmask64 All          = CreateObject | DeleteObject;
  }

  namespace Transform {
    const Bitmask64 Position    = (1 << 2);
    const Bitmask64 Orientation = (1 << 4);
    const Bitmask64 Scale       = (1 << 6);
    const Bitmask64 All         = Position | Orientation | Scale;
  }
}

#endif
