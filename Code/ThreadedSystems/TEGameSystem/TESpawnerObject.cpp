#include "TESpawnerObject.h"

TE::Game::SpawnerObject::SpawnerObject(I32 objectId) : m_objectId(objectId) {}

void TE::Game::SpawnerObject::SetValue(Core::Value &value) {}

void TE::Game::SpawnerObject::Initialize() {}

void TE::Game::SpawnerObject::Cleanup() {}

Bitmask64 TE::Game::SpawnerObject::GetDesiredSystemChanges() { return Engine::Change::NotSet; }

Bitmask64 TE::Game::SpawnerObject::GetPotentialSystemChanges() {
    return Engine::Change::Scene::All;
}

void TE::Game::SpawnerObject::OnSubjectChange(Engine::Subject *subject, Bitmask64 changeBits) {}

I32 TE::Game::SpawnerObject::GetObjectId() const { return m_objectId; }
