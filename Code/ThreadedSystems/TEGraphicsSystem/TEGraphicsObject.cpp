#include "TEGraphicsObject.h"
#include "TEChangeMasks.h"
#include "TEGraphicsSystem.h"
#include "TESpatial.h"

TE::Graphics::GraphicsObject::GraphicsObject(I32 objectId, Enum type, SceneGraph::SceneManager &sceneManager)
    : m_type(type),
      m_sceneManager(sceneManager),
      m_objectId(objectId) {
}

TE::Graphics::GraphicsObject::~GraphicsObject() {
}

Enum TE::Graphics::GraphicsObject::GetType() {
    return m_type;
}

Bitmask64 TE::Graphics::GraphicsObject::GetDesiredSystemChanges() {
    return Engine::Change::Transform::All;
}

TE::SceneGraph::SceneManager &TE::Graphics::GraphicsObject::GetSceneManager() {
    return m_sceneManager;
}

Bitmask64 TE::Graphics::GraphicsObject::GetPotentialSystemChanges() {
    return Engine::Change::NotSet;
}

I32 TE::Graphics::GraphicsObject::GetObjectId() const {
    return m_objectId;
}
