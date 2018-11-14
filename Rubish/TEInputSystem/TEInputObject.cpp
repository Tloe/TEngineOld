#include <TEInputObject.h>
#include "TEDataTypes.h"
#include "TEActions.h"
#include "TEQuaternion.h"
#include "TEVector3D.h"
#include "TEInputSystem.h"
#include "TEProperty.h"

TE::Input::InputObject::InputObject( const std::string& objectString )
	:
	m_objectString(objectString),
	m_objectHash(HashGenerator()(objectString))
{
	
}

Hash TE::Input::InputObject::GetSystemHash()
{
	return Input::GetSystemHash();
}

const std::string& TE::Input::InputObject::GetSystemString()
{
	return Input::GetSystemString();
}

Hash TE::Input::InputObject::GetObjectHash()
{
	return m_objectHash;
}

const std::string& TE::Input::InputObject::GetObjectString()
{
	return m_objectString;
}


Bitmask TE::Input::InputObject::GetDesiredSystemChanges()
{
	return Engine::Change::Transform::All;
}

Bitmask TE::Input::InputObject::GetPotentialSystemChanges()
{
	return Engine::Change::Transform::All;
}

void TE::Input::InputObject::JSONDeserialize( const Json::Value& jsonValue )
{

}

void TE::Input::InputObject::JSONSerialize(Json::Value& jsonValue)
{
	assert(false && "TODO");
}

void TE::Input::InputObject::OnSubjectChange( Subject* subject, Bitmask changeBits )
{
	if (changeBits & Engine::Change::Transform::All)
	{
		Engine::TransformChange* transformChangeInterface = dynamic_cast<Engine::TransformChange*>(subject);

		if (changeBits & Engine::Change::Transform::Position)
		{
			m_position = transformChangeInterface->GetPosition();
		}
		if (changeBits & Engine::Change::Transform::Orientation)
		{
			m_orientation = transformChangeInterface->GetOrientation();
		}
		if (changeBits & Engine::Change::Transform::Scale)
		{
			m_scale = transformChangeInterface->GetScale();
		}
	}
}

TE::Math::Vector3D<Real> TE::Input::InputObject::GetPosition()
{
	return m_position;
}

TE::Math::Quaternion<Real> TE::Input::InputObject::GetOrientation()
{
	return m_orientation;
}

TE::Math::Vector3D<Real> TE::Input::InputObject::GetScale()
{
	return m_scale;
}

void TE::Input::InputObject::TriggerAction( Hash actionHash )
{
	assert(m_actionMap.find(actionHash) != m_actionMap.end() && "Action not in action map of this input object");

	m_actionMap[actionHash]->Execute();
	PostSubjectChanges(Engine::Change::Transform::All);
}

void TE::Input::InputObject::SetProperties( const Engine::PropertyVec& properties )
{

}

void TE::Input::InputObject::GetProperties( Engine::PropertyVec& properties )
{

}
