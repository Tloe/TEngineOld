#include "TERange.h"

F64 TE::InputMapping::ConvertRange(Range &range, F64 rawValue) {
    if (rawValue < range.minInput)
        rawValue = range.minInput;
    else if (rawValue > range.maxInput)
        rawValue = range.maxInput;

    F64 interpolationfactor = (rawValue - range.minInput) / (range.maxInput - range.minInput);
    return (interpolationfactor * (range.maxOutput - range.minOutput)) + range.minOutput;
}
