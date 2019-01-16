#include "TEUniversalScene.h"
#include "TEEngine.h"
#include "TESystem.h"
#include "TEChangeData.h"

TE::Engine::UniversalScene::UniversalScene(const std::string& sceneFilePath,
                                           ChangeSyncer & changeSyncer,
                                           SystemUPtrVec &systems)
	: Resource(sceneFilePath)
	, m_changeSyncer(changeSyncer)
    , m_systems(systems)
    , m_objectId(0)
{

}

TE::Engine::UniversalScene::UniversalScene( UniversalScene&& other )
	: Resource(other.GetFilePath())
    , m_changeSyncer(other.m_changeSyncer)
    , m_systems(other.m_systems)
    , m_objectId(0)
	, m_systemScenes(std::move(other.m_systemScenes))
	, m_universalObjects(std::move(other.m_universalObjects))
{

}

const TE::Engine::SystemSceneUPtrMap& TE::Engine::UniversalScene::GetSystemScenes()
{
	return m_systemScenes;
}

void TE::Engine::UniversalScene::AddSystemScene(U32 systemId, SystemSceneUPtr& systemScene )
{
    m_systemScenes.emplace(std::make_pair(systemId, std::move(systemScene)));
}

void TE::Engine::UniversalScene::Initialize()
{
    for (SystemUPtr& systemPtr : m_systems)
	{
        SystemSceneUPtr systemScene(systemPtr->CreateScene());

        systemScene->Initialize();

        AddSystemScene(systemPtr->GetSystemId(), systemScene);
	}
}

void TE::Engine::UniversalScene::ParseFromFile()
{
	/*Json::Value jsonScene;
	IO::JsonValueFromData(GetDataFront(), GetDataFront()+GetDataSize(), jsonScene);
    JSONDeserialize(jsonScene);*/
}

void TE::Engine::UniversalScene::Cleanup()
{
    m_universalObjects.clear();

    for (auto& itr : m_systemScenes)
    {
        itr.second->Cleanup();
    }

    //m_systemScenes.clear();
    m_objectId = 0;
}

/*void TE::Engine::UniversalScene::JSONDeserialize( const Json::Value& jsonValue )
{
	std::vector<std::string> objectNames = jsonValue.getMemberNames();
	for(std::string & objectName : objectNames)
	{
		UniversalObject & universalObject = CreateUniversalObject(objectName);
		universalObject.JSONDeserialize(jsonValue[objectName]);
	}
}

void TE::Engine::UniversalScene::JSONSerialize(Json::Value& jsonValue)
{

}
*/

const TE::Engine::SystemSceneUPtr& TE::Engine::UniversalScene::GetSystemScene( U32 systemId )
{
    assert(m_systemScenes.find(systemId) != std::end(m_systemScenes) && "System scene not found");

    return m_systemScenes.find(systemId)->second;
}

U32 TE::Engine::UniversalScene::GetSystemId(const std::string &systemName)
{
    auto findItr = std::find_if(std::begin(m_systems), std::end(m_systems),
                                  [&systemName](SystemUPtr & sysPtr) { return sysPtr->GetSystemName() == systemName; } );

    return (*findItr)->GetSystemId();
}

TE::Engine::UniversalObject& TE::Engine::UniversalScene::GetUniversalObject(I32 objectId )
{
    assert(m_universalObjects.find(objectId) != m_universalObjects.end() && "Scene does not contain this object");

    return m_universalObjects.find(objectId)->second;
}

TE::Engine::UniversalObject& TE::Engine::UniversalScene::CreateUniversalObject( const std::string& objectName, I32 objectId )
{
    if(objectId == -1)
        objectId = m_objectId++;

    assert(m_universalObjects.find(objectId) == m_universalObjects.end() && "Universal object id already exists!");

    UniversalObject universalObject(objectName, objectId, *this, m_changeSyncer);
    m_universalObjects.insert(std::make_pair(objectId, std::move(universalObject)));

    return m_universalObjects.find(objectId)->second;
}

void TE::Engine::UniversalScene::OnSubjectChange( Subject* subject, Bitmask64 changeBits )
{
	//Handle scene stuff here
	if (changeBits & Change::Scene::All)
	{
		if (changeBits & Change::Scene::CreateObject)
		{
            auto createObjectData = GetChangeData<Change::CreateObjectData>(subject, Change::Scene::CreateObject);

            auto & universalObject = CreateUniversalObject(createObjectData.objectName);

			U32 objectId = universalObject.GetObjectId();

			for (U32 i = 0; i < createObjectData.systemIds.size(); ++i)
			{
				auto newSystemObject = GetSystemScene(createObjectData.systemIds[i])->CreateSystemObject(createObjectData.objectTypes[i], objectId);

				newSystemObject->SetValue(createObjectData.values[i]);
			}
		}
	}
}
