/**
 *	\file		TEInput.h
 *  \author		Terje Loe
 *  \brief		TEngine input enums. State/input
 */

#ifndef TEINPUT_H
#define	TEINPUT_H

#include "TEDataTypes.h"

#include <map>
#include <assert.h>

namespace TE
{
	namespace InputMapping
	{
		namespace InputState
		{
			enum
			{
				Down      = (1 << 0), 
				Up        = (1 << 1),
				Continued = (1 << 2),
                NotSet      = (1 << 3)
			};
		}

        enum class RangeInput
		{
			MouseDeltaX,
			MouseDeltaY,
			MouseX,
			MouseY
		};

		RangeInput RangeInputFromString(const std::string& str);

		namespace InputType
		{
			std::string ToString(Enum inputType);
			Enum FromString(const std::string& inputType);

			enum
			{
				Key0 = 0,
				Key1,
				Key2,
				Key3,
				Key4,
				Key5,
				Key6,
				Key7,
				Key8,
				Key9,
				KeyA,
				KeyB,
				KeyC,
				KeyD,
				KeyE,
				KeyF,
				KeyG,
				KeyH,
				KeyI,
				KeyJ,
				KeyK,
				KeyL,
				KeyM,
				KeyN,
				KeyO,
				KeyP,
				KeyQ,
				KeyR,
				KeyS,
				KeyT,
				KeyU,
				KeyV,
				KeyW,
				KeyX,
				KeyY,
				KeyZ,
				KeyF1,
				KeyF2,
				KeyF3,
				KeyF4,
				KeyF5,
				KeyF6,
				KeyF7,
				KeyF8,
				KeyF9,
				KeyF10,
				KeyF11,
				KeyF12,
				KeyControlLeft,
				KeyControlRight,
				KeyAltLeft,
				KeyAltRight,
				KeyShiftLeft,
				KeyShiftRight,
				KeySpace,
				KeyEnter,
				KeyEscape,
				KeyBackspace,
				KeyTab,
				KeySeperator,
				KeyCapslock,
				KeyUp,
				KeyDown,
				KeyLeft,
				KeyRight,
				KeyPgUp,
				KeyPgDown,
				KeyHome,
				KeyEnd,
				KeyNum0,
				KeyNum1,
				KeyNum2,
				KeyNum3,
				KeyNum4,
				KeyNum5,
				KeyNum6,
				KeyNum7,
				KeyNum8,
				KeyNum9,
				KeyCollon,
				KeyPlus,
				KeyComma,
				KeyMinus,
				KeyPeriod,
				KeySlashQuest,
				KeyTilde,
				MouseLButton,
				MouseMButton,
				MouseRButton,
				MouseLClick,
				MouseMClick,
				MouseRClick,
				MouseLDoubleClick,
				MouseMDoubleClick,
				MouseRDoubleClick,
				Ascii,
				Count
			};
		}
	}
}
#endif
