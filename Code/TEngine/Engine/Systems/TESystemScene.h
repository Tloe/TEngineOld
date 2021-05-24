#ifndef TESYSTEMSCENE_H
#define TESYSTEMSCENE_H

#include "TEDataTypes.h"
#include <TESystemObject.h>
#include <memory>
#include <string>

namespace TE::Engine {
  class SystemTask;

  class SystemScene {
  public:
    virtual ~SystemScene();

    virtual void Initialize()                                                                = 0;
    virtual void Cleanup()                                                                   = 0;

    virtual SystemTask *GetSystemTask()                                                      = 0;
    virtual SystemObjectSPtr CreateSystemObject(const std::string &objectType, I32 objectId) = 0;
  };

  using SystemSceneUPtr = std::unique_ptr<SystemScene>;
}

#endif
