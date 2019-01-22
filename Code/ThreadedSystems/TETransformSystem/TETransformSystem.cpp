#include <TETransformSystem.h>
#include "TEChangeMasks.h"
#include "TETransformScene.h"
#include "TESystemTask.h"
#include "TEEngine.h"

TE::Transform::TransformSystem::TransformSystem(U32 systemId, const std::string &systemName, Event::EventManager& eventManager)
    : m_systemId(systemId)
    , m_systemName(systemName)
	, m_eventManager(eventManager)
{

}

TE::Transform::TransformSystem::~TransformSystem()
{

}

void TE::Transform::TransformSystem::SetValue(TE::Core::Value &value)
{

}

void TE::Transform::TransformSystem::Startup()
{

}

void TE::Transform::TransformSystem::Shutdown()
{

}

U32 TE::Transform::TransformSystem::GetSystemId()
{
    return m_systemId;
}

const std::string &TE::Transform::TransformSystem::GetSystemName()
{
    return m_systemName;
}

TE::Engine::SystemSceneUPtr TE::Transform::TransformSystem::CreateScene()
{
    return std::make_unique<TransformScene>(m_eventManager);
}


Enum TE::Transform::TransformSystemFactory::ValueFromString(const std::string &valueStr)
{
    assert(false);
    return -1;
}

const std::string &TE::Transform::TransformSystemFactory::GetSystemName()
{
    static std::string name("Transform");
    return name;
}

TE::Engine::SystemUPtr TE::Transform::TransformSystemFactory::Generate(U32 systemId, TE::Engine::EngineRoot &engine, std::vector<Core::Value> &values)
{
    return std::make_unique<TransformSystem>(systemId, "Transform", engine.GetEventManager());
}
