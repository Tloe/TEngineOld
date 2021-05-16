#include "TENetworkTask.h"
#include "TENetworkScene.h"
#include "TENetworkSystem.h"
#include "TEOutgoing.h"

TE::Network::NetworkTask::NetworkTask(NetworkScene &networkScene)
    : m_networkScene(networkScene) {
}

void TE::Network::NetworkTask::Run() {
    m_networkScene.Update(m_deltaTime, m_time);
}

Bitmask TE::Network::NetworkTask::GetTaskFlags() {
    return Engine::TaskFlags::NotSet;
}

void TE::Network::NetworkTask::SetDeltaValues(U64 t, U64 dt) {
    m_deltaTime = dt;
    m_time      = t;
}
