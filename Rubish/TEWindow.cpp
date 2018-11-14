#include <TEWindow.h>
#include <algorithm>
#include <TEInputEvents.h>
#include <TEMathBase.h>

TE::Context::Window::Window()
{
	for (int i = 0; i < 100; ++i) m_previouseInputState[i] = tekInputStateUp;

	m_previouseMousePos[0] = 0;
	m_previouseMousePos[1] = 0;
}

TE::Context::Window::~Window()
{

}

TE::Context::InputMap& TE::Context::Window::GetInputMapRef()
{
	return m_inputMap;
}

int TE::Context::Window::GetPreviousInputState( int i )
{
	assert(i >= 0 && i < 100);
	return m_previouseInputState[i];
}

int TE::Context::Window::GetPreviousMousePos( int i )
{
	assert(i >= 0 && i < 2);
	return m_previouseMousePos[i];
}

void TE::Context::Window::SetPreviousInputState( int i, int state )
{
	m_previouseInputState[i] = state;
}

void TE::Context::Window::SetPreviousMousePos( int i, int pos )
{
	m_previouseMousePos[i] = pos;
}
