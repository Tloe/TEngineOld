#include "TESceneHandler.h"
#include "TEChangeSyncer.h"
#include "TEScheduler.h"

TE::Engine::SceneHandler::SceneHandler(ChangeSyncer &changeSyncer,
                                       TE::IO::FileIO &fileIO,
                                       SystemUPtrVec &systems,
                                       Scheduler &scheduler)
    : m_changeSyncer(changeSyncer),
      m_sceneResourceManager(fileIO),
      m_systems(systems),
      m_scheduler(scheduler) {}

void TE::Engine::SceneHandler::AddSceneFile(const std::string &sceneFile) {
    UniversalScene newScene(sceneFile, m_changeSyncer, m_systems);
    auto sceneHandle = m_sceneResourceManager.AddResource(newScene);
    sceneHandle->Initialize();

    m_sceneFiles.insert(sceneFile);
}

void TE::Engine::SceneHandler::RemoveSceneFile(const std::string &sceneFile) {
    assert(m_sceneResourceManager.IsRegistered(sceneFile) && "Scene has not been loaded");

    auto sceneHandle = m_sceneResourceManager.GetResourceHandle(sceneFile);
    sceneHandle->Cleanup();
    m_changeSyncer.ClearSubscriptions();

    m_sceneResourceManager.RemoveResource(sceneFile);

    m_sceneFiles.erase(sceneFile);
}

void TE::Engine::SceneHandler::SetCurrentScene(const std::string &sceneFile) {
    assert(m_sceneResourceManager.IsRegistered(sceneFile) && "Scene not loaded");

    m_changeSyncer.ClearSubscriptions();
    if (m_currentScene)
        m_currentScene->Cleanup();

    auto sceneHandle = m_sceneResourceManager.GetResourceHandle(sceneFile);
    m_currentScene   = sceneHandle;
    m_currentScene->ParseFromFile();
    m_scheduler.SetScene(*m_currentScene);
}

TE::Engine::UniversalScene &TE::Engine::SceneHandler::GetScene(const std::string &sceneFile) {
    assert(m_sceneResourceManager.IsRegistered(sceneFile) && "Scene not loaded");

    return *m_sceneResourceManager.GetResourceHandle(sceneFile);
}

void TE::Engine::SceneHandler::Cleanup() {
    while (!m_sceneFiles.empty()) {
        RemoveSceneFile(*m_sceneFiles.begin());
    }
}
