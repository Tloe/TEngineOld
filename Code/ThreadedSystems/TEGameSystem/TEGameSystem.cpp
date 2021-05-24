#include "TEGameSystem.h"
#include "TEGameScene.h"

TE::Game::GameSystem::GameSystem(U32 systemId,
                                 const std::string &systemName,
                                 TE::Engine::EngineRoot &engine)
    : m_systemId(systemId),
      m_systemName(systemName) {}

U32 TE::Game::GameSystem::GetSystemId() { return m_systemId; }

const std::string &TE::Game::GameSystem::GetSystemName() { return m_systemName; }

void TE::Game::GameSystem::SetValue(TE::Core::Value &value) {}

void TE::Game::GameSystem::Startup() {}

void TE::Game::GameSystem::Shutdown() {}

TE::Engine::SystemSceneUPtr TE::Game::GameSystem::CreateScene() {
    return std::make_unique<GameScene>();
}

Enum TE::Game::GameSystemFactory::ValueFromString(const std::string &valueStr) {
    assert(false);
    return -1;
}

const std::string &TE::Game::GameSystemFactory::GetSystemName() {
    static std::string name("Game");
    return name;
}

TE::Engine::SystemUPtr TE::Game::GameSystemFactory::Generate(U32 systemId,
                                                             Engine::EngineRoot &engine,
                                                             std::vector<Core::Value> &values) {
    auto gameSystem = std::make_unique<GameSystem>(systemId, "Game", engine);

    for (U32 i = 0; i < values.size(); ++i) {
        gameSystem->SetValue(values[i]);
    }

    return std::move(gameSystem);
}
