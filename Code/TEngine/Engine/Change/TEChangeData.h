#ifndef TECHANGEDATA_H
#define TECHANGEDATA_H

#include <string>
#include <variant>
#include <vector>

#include "TEDataTypes.h"
#include "TEQuaternion.h"
#include "TEValue.h"
#include "TEVector3D.h"

namespace TE {
namespace Engine {
namespace Change {
    struct TransformChange {
        Math::Vector3D<F32> *position;
        Math::Quaternion<F32> *orientation;
        Math::Vector3D<F32> *scale;
    };

    struct CreateObjectData {
        std::string objectName;
        std::vector<U32> systemIds;
        std::vector<std::string> objectTypes;
        std::vector<Core::Value> values;
    };

    typedef std::variant<std::monostate,
                         TransformChange,
                         CreateObjectData>
        ChangeDataPtrVar;

}
}
}
#endif
