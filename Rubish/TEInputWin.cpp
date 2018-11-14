#include <TEInputWin.h>

TE::Input::InputWin::InputWin() : InputHandler(WinKeyMapInitializer())
{

}

TE::Input::InputWin::~InputWin()
{

}

bool TE::Input::InputWin::IsDown( const Key key, const KeyMap& keyMap )
{
	if (GetActiveWindow())
	{
		KeyMap::const_iterator itr = keyMap.find(key);
		if(GetKeyState(itr->second) & 0x80)
			return true;
	}

	return false;
}

void TE::Input::InputWin::GetMousePos( int& x, int& y )
{
	DWORD pos = GetMessagePos();
	x = GET_X_LPARAM(pos);
	y = GET_Y_LPARAM(pos);
}

#endif