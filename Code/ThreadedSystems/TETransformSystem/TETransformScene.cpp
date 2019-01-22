#include <TETransformScene.h>
#include "TEChangeMasks.h"
#include "TETransformObject.h"
#include "TESystemTask.h"
#include "TETransformSystem.h"

TE::Transform::TransformScene::TransformScene(Event::EventManager &eventManager)
	: m_eventManager(eventManager)
{

}

TE::Transform::TransformScene::~TransformScene()
{

}

TE::Engine::SystemTask* TE::Transform::TransformScene::GetSystemTask()
{
	return nullptr;
}

TE::Engine::SystemObjectSPtr TE::Transform::TransformScene::CreateSystemObject(const std::string& objectType, I32 objectId)
{
    if (objectType == "TransformObject")
    {
        return std::make_shared<TransformObject>(objectId, m_eventManager);
    }
    return TE::Engine::SystemObjectSPtr(nullptr);
}

void TE::Transform::TransformScene::Initialize()
{

}

void TE::Transform::TransformScene::Cleanup()
{

}
