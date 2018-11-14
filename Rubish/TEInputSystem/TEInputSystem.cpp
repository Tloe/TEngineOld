#include <TEInputSystem.h>
#include "TESystemTypes.h"
#include "TEInputScene.h"
#include "TEInputProperties.h"

Hash TE::Input::GetSystemHash()
{
	static Hash hash = HashGenerator()("Input");
	return hash;
}

const std::string& TE::Input::GetSystemString()
{
	static std::string str = "Input";
	return str;
}


TE::Input::InputSystem::InputSystem(Platform::PlatformWindow& platformWindow)
	:
	m_platformWindow(platformWindow),
	m_inputGroup(0)
{

}

TE::Input::InputSystem::~InputSystem()
{

}

void TE::Input::InputSystem::Initialize()
{

}

void TE::Input::InputSystem::Cleanup()
{

}

Hash TE::Input::InputSystem::GetSystemHash()
{
	return Input::GetSystemHash();
}

const std::string& TE::Input::InputSystem::GetSystemString()
{
	return Input::GetSystemString();
}

TE::Engine::SystemSceneUPtr TE::Input::InputSystem::CreateScene()
{
	return Engine::SystemSceneUPtr(new InputScene(*this, m_platformWindow));
}

void TE::Input::InputSystem::SetProperties( const Engine::PropertyVec& properties )
{
	for (auto& itr : properties)
	{
		if (itr.GetPropertyType() == Input::PropertyType::InputAction::TransformPosition)
		{

		}
	}
}

void TE::Input::InputSystem::GetProperties( Engine::PropertyVec& properties )
{

}

bool TE::Input::InputSystem::GetMapping( Enum teInput, InputMapping& inputMapping )
{
	auto findItr = m_inputMappings[m_inputGroup].find(teInput);
	if (findItr != m_inputMappings[m_inputGroup].end())
	{
		inputMapping = findItr->second;
		return true;
	}
	return false;
}

void TE::Input::InputSystem::SetMapping(Enum inputGroup,
										const std::string& inputString,
										Enum teInput, 
										Bitmask inputStateFlags,
										Hash objectHash,
										Hash actionHash)
{
	InputMapping newInputMapping = { inputString, 
									 inputStateFlags,
									 objectHash,
									 actionHash };
	
	m_inputMappings[inputGroup][teInput] = newInputMapping;
}