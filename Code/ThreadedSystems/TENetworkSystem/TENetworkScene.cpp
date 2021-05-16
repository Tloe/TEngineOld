#include "TENetworkScene.h"
#include "TENetworkObject.h"
#include "TESystemTask.h"
#include "TETime.h"

TE::Network::NetworkScene::NetworkScene(Event::EventManager &eventManager, NetworkManager &networkManager)
    : m_networkTask(*this),
      m_networkManager(networkManager),
      m_eventManager(eventManager) {
}

void TE::Network::NetworkScene::Initialize() {
}

void TE::Network::NetworkScene::Cleanup() {
}

TE::Engine::SystemTask *TE::Network::NetworkScene::GetSystemTask() {
    return &m_networkTask;
}

TE::Engine::SystemObjectSPtr TE::Network::NetworkScene::CreateSystemObject(const std::string &objectType, I32 objectId) {
    if (objectType == "NetworkObject") {
        auto networkObject = std::make_shared<NetworkObject>(objectId, m_eventManager, m_networkManager.GetMessagehandler());

        m_networkManager.AddNetworkObject(objectId, networkObject);

        return networkObject;
    }

    return Engine::SystemObjectSPtr(nullptr);
}

void TE::Network::NetworkScene::Update(U64 deltaTime, U64 time) {
    m_networkManager.Update(deltaTime, time);
}
