#include "TEGameScene.h"
#include "TEActorObject.h"
#include "TESpawnerObject.h"

#include <memory>

TE::Game::GameScene::GameScene()
	: m_gameTask(*this)
{

}

void TE::Game::GameScene::Initialize()
{

}

void TE::Game::GameScene::Cleanup()
{

}

TE::Engine::SystemTask* TE::Game::GameScene::GetSystemTask()
{
    return &m_gameTask;
}

TE::Engine::SystemObjectSPtr TE::Game::GameScene::CreateSystemObject(const std::string &objectType, I32 objectId)
{
    if(objectType == "ActorObject")
    {
        return std::make_shared<ActorObject>(objectId);
    }
	else if(objectType == "SpawnerObject")
	{
		return std::make_shared<SpawnerObject>(objectId);
	}

    return std::shared_ptr<Engine::SystemObject>(nullptr);
}

void TE::Game::GameScene::Update()
{

}
