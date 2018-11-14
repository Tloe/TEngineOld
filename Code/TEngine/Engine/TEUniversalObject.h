#ifndef TEUNIVERSALOBJECT_H
#define TEUNIVERSALOBJECT_H

#include "TESystemObject.h"
#include "TEJson.h"
#include "TEDataTypes.h"

#include <map>

namespace TE
{
	namespace Engine { class UniversalScene; }
	namespace Engine { class ChangeSyncer; }
	
	namespace Engine
	{
		class UniversalObject// : public IO::JsonSerializer
		{
		public:
			UniversalObject(const std::string& objectName,
                            I32 objectId,
                            UniversalScene& universalScene,
                            ChangeSyncer & changeSyncer);
			UniversalObject(UniversalObject&& other);
            ~UniversalObject();

            //virtual void JSONDeserialize( const Json::Value& jsonValue );
            //virtual void JSONSerialize(Json::Value& jsonValue);

            I32 GetObjectId() const;
            void Cleanup();
            SystemObject& GetSystemObject(U32 systemId);
            void RegisterSubjectChangesWithSystemObjects(Subject* subject, Bitmask64 potentialSystemChanges);
            void UnRegisterSubjectChangesWithSystemObjects(Subject* subject);

            void AddSystemObject(U32 systemId, const SystemObjectSPtr &systemObject);
            void RemoveSystemObject(U32 systemId);

		private:
            typedef std::map<U32, SystemObjectSPtr> SystemObjectSPtrMap;

            std::string m_objectName;
            I32 m_objectId;
            SystemObjectSPtrMap m_systemObjects;
			UniversalScene & m_universalScene;
			ChangeSyncer & m_changeSyncer;
		};

		typedef std::unique_ptr<UniversalObject> UniversalObjectUPtr;
	}
}

#endif
