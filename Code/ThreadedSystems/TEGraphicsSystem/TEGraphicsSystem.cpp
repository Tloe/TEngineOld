#include "TEGraphicsSystem.h"
#include "TEChangeMasks.h"
#include "TEEngine.h"
#include "TEEventManager.h"
#include "TEFileLoader.h"
#include "TEGraphicsScene.h"
#include "TEGraphicsTask.h"
#include "TERenderer.h"
#include "TEResolutionEvent.h"
#include "TESceneManager.h"

#include <sstream>

TE::Graphics::GraphicsSystem::GraphicsSystem(U32 systemId, const std::string &systemName, Platform::OSWinId osWinId, IO::FileIO &fileIO, Event::EventManager &eventManager)
    : m_systemId(systemId),
      m_systemName(systemName),
      m_renderer(osWinId, fileIO),
      m_sceneManager(m_renderer),
      m_eventManager(eventManager) {
    m_eventManager.Subscribe<Event::ResolutionEvent>(this);
}

TE::Graphics::GraphicsSystem::GraphicsSystem(U32 systemId, const std::string &systemName, TE::IO::FileIO &fileIO, TE::Event::EventManager &eventManager)
    : m_systemId(systemId),
      m_systemName(systemName),
      m_renderer(fileIO),
      m_sceneManager(m_renderer),
      m_eventManager(eventManager) {
    m_eventManager.Subscribe<Event::ResolutionEvent>(this);
}

TE::Graphics::GraphicsSystem::~GraphicsSystem() {
    m_eventManager.UnSubscribe<Event::ResolutionEvent>(this);
}

void TE::Graphics::GraphicsSystem::SetValue(TE::Core::Value &value) {
    switch (value.GetValueType()) {
    case Values::WindowTitle: {
        m_renderer.GetPlatformWindow().SetWindowTitle(value.GetString());
    } break;
    case Values::InputFile: {
        m_renderer.GetPlatformWindow().LoadInputFile(value.GetString());
    } break;
    case Values::Resolution: {
        std::stringstream ss;

        bool fullscreen = false;
        if (value.GetString() == "true")
            fullscreen = true;

        I32 width;
        ss << value.GetString();
        ss >> width;
        ss.clear();

        I32 height;
        ss << value.GetString();
        ss >> height;
        ss.clear();

        I32 viewportWidth;
        ss << value.GetString();
        ss >> viewportWidth;
        ss.clear();

        I32 viewportHeight;
        ss << value.GetString();
        ss >> viewportHeight;
        ss.clear();

        bool updateViewPort = false;
        if (value.GetString() == "true")
            updateViewPort = true;

        I32 positionX;
        ss << value.GetString();
        ss >> positionX;
        ss.clear();

        I32 positionY;
        ss << value.GetString();
        ss >> positionY;
        ss.clear();

        Event::ResolutionEvent resolutionEvent(fullscreen,
                                               updateViewPort,
                                               width,
                                               height,
                                               viewportWidth,
                                               viewportHeight,
                                               positionX,
                                               positionY);
        m_eventManager.QueEvent(resolutionEvent);
    } break;
    }
}

void TE::Graphics::GraphicsSystem::Startup() {
    m_renderer.Startup();
}

void TE::Graphics::GraphicsSystem::Shutdown() {
    m_renderer.Shutdown();
}

U32 TE::Graphics::GraphicsSystem::GetSystemId() {
    return m_systemId;
}

const std::string &TE::Graphics::GraphicsSystem::GetSystemName() {
    return m_systemName;
}

TE::Engine::SystemSceneUPtr TE::Graphics::GraphicsSystem::CreateScene() {
    return std::make_unique<GraphicsScene>(m_sceneManager);
}

void TE::Graphics::GraphicsSystem::HandleEvent(Event::ResolutionEvent &resolutionEvent) {
    if (resolutionEvent.GetFullscreen()) {
        m_renderer.SetFullscreen(resolutionEvent.GetWidth(),
                                 resolutionEvent.GetHeight(),
                                 resolutionEvent.GetUpdateViewport());
    } else {
        m_renderer.SetWindowed(resolutionEvent.GetWidth(),
                               resolutionEvent.GetHeight(),
                               resolutionEvent.GetViewportWidth(),
                               resolutionEvent.GetViewportHeight(),
                               resolutionEvent.GetUpdateViewport(),
                               resolutionEvent.GetPositionX(),
                               resolutionEvent.GetPositionY());
    }
}

TE::Platform::PlatformWindow &TE::Graphics::GraphicsSystem::GetPlatformWindow() {
    return m_renderer.GetPlatformWindow();
}

TE::Graphics::GraphicsSystemFactory::GraphicsSystemFactory(Platform::OSWinId osWinId)
    : m_osWinId(osWinId) {
}

Enum TE::Graphics::GraphicsSystemFactory::ValueFromString(const std::string &valueStr) {
    if (valueStr == "WindowTitle")
        return GraphicsSystem::Values::WindowTitle;
    if (valueStr == "InputFile")
        return GraphicsSystem::Values::InputFile;
    if (valueStr == "Resolution")
        return GraphicsSystem::Values::Resolution;

    assert(false);
    return -1;
}

const std::string &TE::Graphics::GraphicsSystemFactory::GetSystemName() {
    static std::string name("Graphics");
    return name;
}

TE::Engine::SystemUPtr TE::Graphics::GraphicsSystemFactory::Generate(U32 systemId, TE::Engine::EngineRoot &engine, std::vector<Core::Value> &values) {
    std::unique_ptr<GraphicsSystem> graphicsSystem(nullptr);

    if (m_osWinId) {
        graphicsSystem = std::make_unique<GraphicsSystem>(0, "Graphics", m_osWinId, engine.GetFileIO(), engine.GetEventManager());
    } else {
        graphicsSystem = std::make_unique<GraphicsSystem>(0, "Graphics", engine.GetFileIO(), engine.GetEventManager());
    }

    for (U32 i = 0; i < values.size(); ++i) {
        graphicsSystem->SetValue(values[i]);
    }

    return std::move(graphicsSystem);
}
