#include "TEUniversalObject.h"
#include "TEEngine.h"
#include "TESystem.h"
#include "TEUniversalScene.h"

TE::Engine::UniversalObject::UniversalObject(const std::string &objectName, I32 objectId,
                                             UniversalScene &universalScene,
                                             ChangeSyncer &changeSyncer)
    : m_objectName(objectName),
      m_objectId(objectId),
      m_universalScene(universalScene),
      m_changeSyncer(changeSyncer) {
}

TE::Engine::UniversalObject::UniversalObject(UniversalObject &&other)
    : m_objectName(std::move(other.m_objectName)),
      m_objectId(other.m_objectId),
      m_systemObjects(std::move(other.m_systemObjects)),
      m_universalScene(other.m_universalScene),
      m_changeSyncer(other.m_changeSyncer) {
}

TE::Engine::UniversalObject::~UniversalObject() {
    for (auto &itr : m_systemObjects) {
        itr.second->Cleanup();
    }
}

I32 TE::Engine::UniversalObject::GetObjectId() const {
    return m_objectId;
}

TE::Engine::SystemObject &TE::Engine::UniversalObject::GetSystemObject(U32 systemId) {
    assert(m_systemObjects.find(systemId) != std::end(m_systemObjects) && "Object doesn't have this system object");

    return *m_systemObjects[systemId];
}

void TE::Engine::UniversalObject::RegisterSubjectChangesWithSystemObjects(TE::Engine::Subject *subject, Bitmask64 potentialSystemChanges) {
    for (auto &itr : m_systemObjects) {
        if (itr.second->GetDesiredSystemChanges() & potentialSystemChanges) {
            m_changeSyncer.RegisterChangeSubscription(subject,
                                                      itr.second->GetDesiredSystemChanges(),
                                                      itr.second.get(),
                                                      itr.second->GetDesiredSystemChanges());
        }
    }
}

void TE::Engine::UniversalObject::UnRegisterSubjectChangesWithSystemObjects(TE::Engine::Subject *subject) {
    assert(false && "Unregister with m_changeSyncer. (need function in m_changeSyncer)");
}

void TE::Engine::UniversalObject::AddSystemObject(U32 systemId, const SystemObjectSPtr &systemObject) {
    for (auto &itr : m_systemObjects) {
        if (systemObject->GetDesiredSystemChanges() & itr.second->GetPotentialSystemChanges()) {
            m_changeSyncer.RegisterChangeSubscription(itr.second.get(),
                                                      systemObject->GetDesiredSystemChanges(),
                                                      systemObject.get(),
                                                      systemObject->GetDesiredSystemChanges());
        }
        if (itr.second->GetDesiredSystemChanges() & systemObject->GetPotentialSystemChanges()) {
            m_changeSyncer.RegisterChangeSubscription(systemObject.get(),
                                                      itr.second->GetDesiredSystemChanges(),
                                                      itr.second.get(),
                                                      itr.second->GetDesiredSystemChanges());
        }
    }

    systemObject->Initialize();
    m_systemObjects.insert(std::make_pair(systemId, systemObject));
}

void TE::Engine::UniversalObject::RemoveSystemObject(U32 systemId) {
    auto itr = m_systemObjects.find(systemId);
    itr->second->Cleanup();
    m_systemObjects.erase(itr);
    assert(false && "Unregister with m_changeSyncer. (need function in m_changeSyncer)");
}

/*void TE::Engine::UniversalObject::JSONDeserialize( const Json::Value& jsonValue )
{
    std::vector<std::string> systemNames = jsonValue.getMemberNames();
    for(std::string & systemName : systemNames)
        {
        U32 systemId = m_universalScene.GetSystemId(systemName);
        const SystemSceneUPtr& systemScene = m_universalScene.GetSystemScene(systemId);

        const Json::Value & jsonSystem = jsonValue[systemName];
        std::vector<std::string> objectTypes = jsonSystem.getMemberNames();
        for(std::string & objectType : objectTypes)
                {
            SystemObjectSPtr systemObject = systemScene->CreateSystemObject(objectType, m_objectId);

            systemObject->JSONDeserialize(jsonSystem[objectType]);

            AddSystemObject(systemId, systemObject);
                }
        }
}

void TE::Engine::UniversalObject::JSONSerialize(Json::Value& jsonValue)
{

}
*/