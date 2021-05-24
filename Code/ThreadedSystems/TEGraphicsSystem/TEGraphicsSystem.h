#ifndef TEGRAPHICSSYSTEM_H
#define TEGRAPHICSSYSTEM_H

#include "TEDataTypes.h"
#include "TEEventHandler.h"
#include "TESystem.h"
#include <TERenderer.h>
#include <TESceneManager.h>

namespace TE::Platform {
  class PlatformWindow;
}

namespace TE::IO {
  class FileIO;
}

namespace TE::Event {
  class ResolutionEvent;
  class EventManager;
}

namespace TE::Graphics {
  class GraphicsSystem : public Engine::System, public Event::EventHandler {
  public:
    struct Values {
      enum { WindowTitle, InputFile, Resolution };
    };

    GraphicsSystem(U32 systemId,
                   const std::string &systemName,
                   Platform::OSWinId osWinId,
                   IO::FileIO &fileIO,
                   Event::EventManager &eventManager);
    GraphicsSystem(U32 systemId,
                   const std::string &systemName,
                   IO::FileIO &fileIO,
                   Event::EventManager &eventManager);
    ~GraphicsSystem();

    virtual U32 GetSystemId();
    virtual const std::string &GetSystemName();
    virtual void SetValue(Core::Value &value);
    virtual void Startup();
    virtual void Shutdown();
    virtual Engine::SystemSceneUPtr CreateScene();
    virtual void HandleEvent(Event::ResolutionEvent &resolutionEvent);

    Platform::PlatformWindow &GetPlatformWindow();

  private:
    U32 m_systemId;
    std::string m_systemName;
    Render::Renderer m_renderer;
    SceneGraph::SceneManager m_sceneManager;
    Event::EventManager &m_eventManager;
  };

  class GraphicsSystemFactory : public Engine::SystemFactory {
  public:
    GraphicsSystemFactory(Platform::OSWinId osWinId = 0);
    virtual Enum ValueFromString(const std::string &valueStr);
    virtual const std::string &GetSystemName();
    virtual Engine::SystemUPtr
    Generate(U32 systemId, Engine::EngineRoot &engine, std::vector<Core::Value> &values);

  private:
    Platform::OSWinId m_osWinId;
  };
}

#endif
