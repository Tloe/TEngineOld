#ifndef TENETWORKSYSTEM_H
#define TENETWORKSYSTEM_H

#include "TENetworkManager.h"
#include "TEOutgoing.h"
#include "TESystem.h"

#include <string>

namespace TE::Engine {
  class EngineRoot;
}
namespace TE::Event {
  class EventManager;
}

namespace TE::Network {
  class NetworkSystem : public Engine::System {
  public:
    struct Values {
      enum { Mode, Port, IpFamily, Connect };
    };

    NetworkSystem(U32 systemId, const std::string &systemName, Engine::EngineRoot &engine);
    ~NetworkSystem();

    virtual U32 GetSystemId();
    virtual const std::string &GetSystemName();
    virtual void SetValue(Core::Value &value);
    virtual void Startup();
    virtual void Shutdown();
    virtual Engine::SystemSceneUPtr CreateScene();
    NetworkManager &GetNetworkManager();

  private:
    U32 m_systemId;
    std::string m_systemName;
    Event::EventManager &m_eventManager;
    NetworkManager m_networkManager;
  };

  class NetworkSystemFactory : public Engine::SystemFactory {
  public:
    virtual Enum ValueFromString(const std::string &valueStr);
    virtual const std::string &GetSystemName();
    virtual Engine::SystemUPtr
    Generate(U32 systemId, Engine::EngineRoot &engine, std::vector<Core::Value> &values);
  };
}

#endif
