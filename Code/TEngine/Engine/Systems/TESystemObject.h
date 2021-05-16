#ifndef TESYSTEMOBJECT_H
#define TESYSTEMOBJECT_H

#include "TEChangeMasks.h"
#include "TEDataTypes.h"
#include "TEJson.h"
#include "TEObserver.h"
#include "TESubject.h"

#include <memory>
#include <string>
#include <unordered_map>

namespace TE {
    namespace Core {
        class Value;
    }

    namespace Engine {
        class SystemObject : public Observer, public Subject //, public IO::JsonSerializer
        {
          public:
            virtual void SetValue(Core::Value &value)     = 0;
            virtual void Initialize()                     = 0;
            virtual void Cleanup()                        = 0;
            virtual Bitmask64 GetDesiredSystemChanges()   = 0;
            virtual Bitmask64 GetPotentialSystemChanges() = 0;
            virtual I32 GetObjectId() const               = 0;
        };

        typedef std::shared_ptr<SystemObject> SystemObjectSPtr;
        typedef std::weak_ptr<SystemObject> SystemObjectWPtr;
    }
}

#endif
