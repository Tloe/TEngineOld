#ifndef TEINPUTOBJECT_H
#define TEINPUTOBJECT_H

#include <memory>
#include "TEDataTypes.h"
#include <TESystemObject.h>
#include "TEActions.h"
#include "TETransformChange.h"
#include "TEQuaternion.h"
#include "TEVector3D.h"

namespace TE
{
	namespace Engine { class Property; typedef std::vector<Property> PropertyVec; }

	namespace Input
	{
		class InputObject : public Engine::SystemObject, public Engine::TransformChange
		{
		public:
			InputObject(const std::string& objectString);
			
			virtual void SetProperties( const Engine::PropertyVec& properties );
			virtual void GetProperties( Engine::PropertyVec& properties );
			virtual Hash GetSystemHash();
			virtual const std::string& GetSystemString();
			virtual Hash GetObjectHash();
			virtual const std::string& GetObjectString();
			virtual Bitmask GetDesiredSystemChanges();
			virtual Bitmask GetPotentialSystemChanges();
			virtual void JSONDeserialize( const Json::Value& jsonValue );
			virtual void JSONSerialize(Json::Value& jsonValue);
			virtual void OnSubjectChange( Engine::Subject* subject, Bitmask changeBits );
			virtual Math::Vector3D<Real> GetPosition();
			virtual Math::Quaternion<Real> GetOrientation();
			virtual Math::Vector3D<Real> GetScale();
			void TriggerAction(Hash actionHash);

		private:
			typedef std::unordered_map<Hash, ActionUPtr> ActionNameMap;

			std::string m_objectString;
			Hash m_objectHash;
			Math::Vector3D<Real> m_position;
			Math::Vector3D<Real> m_scale;
			Math::Quaternion<Real> m_orientation;
			ActionNameMap m_actionMap;
		};
	}
}

#endif