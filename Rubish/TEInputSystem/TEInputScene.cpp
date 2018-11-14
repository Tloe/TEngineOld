#include <TEInputScene.h>
#include "TEInputObject.h"
#include "TEInput.h"
#include <TEPlatformWindowIncludes.h>
#include "TEInputSystem.h"
#include "TEProperty.h"

TE::Input::InputScene::InputScene(InputSystem& inputSystem, Platform::PlatformWindow& platformWindow)
	:
	m_inputTask(*this),
	m_platformWindow(platformWindow),
	m_inputSystem(inputSystem)
{

}

void TE::Input::InputScene::Initialize()
{

}

void TE::Input::InputScene::Cleanup()
{

}

Hash TE::Input::InputScene::GetSystemHash()
{
	return Input::GetSystemHash();
}

const std::string& TE::Input::InputScene::GetSystemString()
{
	return Input::GetSystemString();
}

TE::Engine::SystemTask* TE::Input::InputScene::GetSystemTask()
{
	return &m_inputTask;
}

TE::Engine::SystemObject* TE::Input::InputScene::CreateSystemObject( const std::string& objectTypeStr, const std::string& objectName )
{
	InputObject* inputObject = new InputObject(objectName);
	m_inputObjects.push_back(inputObject);
	return inputObject;
}

void TE::Input::InputScene::DestroySystemObject( Engine::SystemObject* systemObject )
{
	InputObject* inputObject = static_cast<InputObject*>(systemObject);
	m_inputObjects.remove(inputObject);
	delete inputObject;
}

TE::Input::InputObject* TE::Input::InputScene::FindInputObject(Hash objectHash)
{
	auto itr = find_if(m_inputObjects.begin(), m_inputObjects.end(), [objectHash](InputObject* obj){ return obj->GetObjectHash() == objectHash; });

	if (itr != m_inputObjects.end())
		return *itr;
	
	return nullptr;
}

void TE::Input::InputScene::InputUpdate()
{
	Platform::PlatformInputEvent platformInputEvent;
	InputMapping inputMapping;

	std::list<InputMapping> inputReceived;

	while (m_platformWindow.PullNextPlatformInput(platformInputEvent))
	{
		if(m_inputSystem.GetMapping(platformInputEvent.inputType, inputMapping))
		{
			inputReceived.push_back(inputMapping);
		}
	}

	for (auto& receivedItr : inputReceived)
	{
		for(auto& inputObjItr : m_inputObjects)
		{
			if(inputObjItr->GetObjectHash() == receivedItr.objectHash)
			{
				inputObjItr->TriggerAction(receivedItr.actionHash);
			}
		}
	}
}

void TE::Input::InputScene::SetProperties( const Engine::PropertyVec& properties )
{

}

void TE::Input::InputScene::GetProperties( Engine::PropertyVec& properties )
{

}

