#ifndef TESYSTEM_H
#define TESYSTEM_H

#include "TEDataTypes.h"
#include "TEValue.h"

#include <memory>
#include <string>
#include <vector>

namespace TE::Engine {
  class EngineRoot;

  class SystemScene;
  using SystemSceneUPtr = std::unique_ptr<SystemScene>;

  class System {
  public:
    virtual ~System();

    virtual U32 GetSystemId()                  = 0;
    virtual const std::string &GetSystemName() = 0;
    virtual void SetValue(Core::Value &value)  = 0;
    virtual void Startup()                     = 0;
    virtual void Shutdown()                    = 0;
    virtual SystemSceneUPtr CreateScene()      = 0;
  };

  using SystemUPtr    = std::unique_ptr<System>;
  using SystemUPtrVec = std::vector<SystemUPtr>;

  class SystemFactory {
  public:
    virtual Enum ValueFromString(const std::string &valueStr) = 0;
    virtual const std::string &GetSystemName()                = 0;
    virtual SystemUPtr
    Generate(U32 systemId, EngineRoot &engine, std::vector<Core::Value> &values) = 0;
  };
}

#endif
