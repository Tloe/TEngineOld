#ifndef TETRANSFORMSYSTEM_H
#define TETRANSFORMSYSTEM_H

#include <TESystem.h>
#include <TESystemScene.h>

namespace TE::Engine {
  class SystemTask;
}
namespace TE::Event {
  class EventManager;
}

namespace TE::Transform {
  class TransformSystem : public Engine::System {
  public:
    TransformSystem(U32 systemId, const std::string &systemName, Event::EventManager &eventManager);
    virtual ~TransformSystem();

    virtual U32 GetSystemId();
    virtual const std::string &GetSystemName();
    virtual void SetValue(Core::Value &value);
    virtual void Startup();
    virtual void Shutdown();
    virtual Engine::SystemSceneUPtr CreateScene();

  private:
    U32 m_systemId;
    std::string m_systemName;
    Event::EventManager &m_eventManager;
  };

  class TransformSystemFactory : public Engine::SystemFactory {
  public:
    virtual Enum ValueFromString(const std::string &valueStr);
    virtual const std::string &GetSystemName();
    virtual Engine::SystemUPtr
    Generate(U32 systemId, Engine::EngineRoot &engine, std::vector<Core::Value> &values);
  };
}

#endif
