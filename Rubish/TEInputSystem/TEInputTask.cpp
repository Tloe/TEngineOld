#include <TEInputTask.h>
#include <TEInputScene.h>
#include "TEInputSystem.h"

TE::Input::InputTask::InputTask( InputScene& inputScene )
	:
	m_inputScene(inputScene)
{

}

Hash TE::Input::InputTask::GetSystemHash()
{
	return Input::GetSystemHash();
}

const std::string& TE::Input::InputTask::GetSystemString()
{
	return Input::GetSystemString();
}

void TE::Input::InputTask::SetDeltaValues( U64 t, U64 dt )
{
	
}

void TE::Input::InputTask::TaskExecution( bool threaded )
{
	m_inputScene.InputUpdate();
}

Bitmask TE::Input::InputTask::GetTaskFlags()
{
	return Engine::TaskFlags::NotSet;
}