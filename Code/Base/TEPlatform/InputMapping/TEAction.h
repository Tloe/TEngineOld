#ifndef TEACTION_H
#define TEACTION_H

#include "TEDataTypes.h"
#include "TEInput.h"

namespace TE {
namespace InputMapping {
    struct Action {
        std::string name;
        Hash nameHash;
        TE::InputMapping::InputType defaultKey;
        TE::InputMapping::InputType userKey;
    };
}
}

#endif