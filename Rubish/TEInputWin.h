#include <TEDefines.h>

#ifndef TEINPUTWIN_H
#define TEINPUTWIN_H

#include "TEInput.h"
#include <Windows.h>
#include <winuser.h>
#include <TEKeys.h>
#include <Windowsx.h>

namespace TE
{
	namespace Input
	{
		struct WinKeyMapInitializer
		{
			void operator()(KeyMap& keyMap);
		};

		class InputWin : public InputBase
		{
		public:
			InputWin();

			~InputWin();
		private:
			bool IsDown(const Key key, const KeyMap& keyMap);
			void GetMousePos(int& x, int& y);
		};
	}
}

#endif