#include "TEGraphicsScene.h"
#include "TEChangeMasks.h"
#include "TESystemTask.h"
#include "TERenderableObject.h"
#include "TECameraObject.h"
#include "TESceneManager.h"
#include "TEGraphicsSystem.h"

TE::Graphics::GraphicsScene::GraphicsScene( SceneGraph::SceneManager& sceneManager)
	:
	m_sceneManager(sceneManager),
	m_graphicsTask(sceneManager)
{

}

TE::Engine::SystemTask* TE::Graphics::GraphicsScene::GetSystemTask()
{
	return &m_graphicsTask;
}

TE::Engine::SystemObjectSPtr TE::Graphics::GraphicsScene::CreateSystemObject(const std::string& objectType, I32 objectId)
{
    if (objectType == "RenderableObject")
    {
        return std::make_shared<RenderableObject>(objectId, m_sceneManager);
	}
    else if(objectType == "CameraObject")
    {
        return std::make_shared<CameraObject>(objectId, m_sceneManager);
	}

    return Engine::SystemObjectSPtr(nullptr);
}

void TE::Graphics::GraphicsScene::Initialize()
{

}

void TE::Graphics::GraphicsScene::Cleanup()
{

}
