#ifndef TERANGE_H
#define TERANGE_H

#include "TEDataTypes.h"
#include "TEInput.h"

namespace TE {
namespace InputMapping {
    struct Range {
        std::string name;
        Hash nameHash;
        RangeInput defaultRange;
        RangeInput userRange;
        U32 defaultSensitivity;
        U32 userSensitivity;
        F64 minInput;
        F64 maxInput;
        F64 minOutput;
        F64 maxOutput;
    };

    F64 ConvertRange(Range &range, F64 rawValue);
}
}

#endif