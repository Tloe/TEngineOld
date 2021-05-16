#ifndef TESYSTEMSCENE_H
#define TESYSTEMSCENE_H

#include "TEDataTypes.h"
#include <TESystemObject.h>
#include <memory>
#include <string>

namespace TE {
    namespace Engine {
        class SystemTask;
    }

    namespace Engine {
        class SystemScene {
          public:
            virtual ~SystemScene();

            virtual void Initialize()                                                                = 0;
            virtual void Cleanup()                                                                   = 0;

            virtual SystemTask *GetSystemTask()                                                      = 0;
            virtual SystemObjectSPtr CreateSystemObject(const std::string &objectType, I32 objectId) = 0;
        };

        typedef std::unique_ptr<SystemScene> SystemSceneUPtr;
    }
}

#endif
