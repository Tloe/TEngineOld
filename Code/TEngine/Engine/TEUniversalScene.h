#ifndef TEUNIVERSALSCENE_H
#define TEUNIVERSALSCENE_H

#include "TEDataTypes.h"
#include "TEFileIO.h"
#include "TEResource.h"
#include "TESystem.h"
#include "TESystemScene.h"
#include "TEUniversalObject.h"

#include <unordered_map>

namespace TE {
    namespace Engine {
        class ChangeSyncer;
    }

    namespace Engine {
        typedef std::unordered_map<U32, SystemSceneUPtr> SystemSceneUPtrMap;

        class UniversalScene
            : public Resources::Resource,
              public Observer
        //, public IO::JsonSerializer
        {
          public:
            UniversalScene(const std::string &sceneFilePath,
                           ChangeSyncer &changeSyncer,
                           SystemUPtrVec &systems);
            UniversalScene(UniversalScene &&other);

            void Initialize();
            void Cleanup();
            void ParseFromFile();
            void CleanupSystemScenes();
            void AddSystemScene(U32 systemId, SystemSceneUPtr &systemScene);
            UniversalObject &GetUniversalObject(I32 objectId);
            UniversalObject &CreateUniversalObject(const std::string &objectName, I32 objectId = -1);
            U32 GetSystemId(const std::string &systemName);
            const SystemSceneUPtr &GetSystemScene(U32 systemId);
            const SystemSceneUPtrMap &GetSystemScenes();
            // virtual void JSONDeserialize( const Json::Value& jsonValue );
            // virtual void JSONSerialize(Json::Value& jsonValue);
            virtual void OnSubjectChange(Subject *subject, Bitmask64 changeBits);

          private:
            typedef std::unordered_map<I32, UniversalObject> UniversalObjectMap;

            ChangeSyncer &m_changeSyncer;
            SystemUPtrVec &m_systems;
            I32 m_objectId;
            SystemSceneUPtrMap m_systemScenes;
            UniversalObjectMap m_universalObjects;
        };
    }
}

#endif
