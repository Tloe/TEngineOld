#ifndef TEWINDOWMS_H
#define TEWINDOWMS_H

#include <TEInputMap.h>
#include <TEColor.h>
#include <string>

namespace TE
{
	namespace Context
	{
		class Window
		{
		public:
			Window();
			virtual ~Window();

			InputMap& GetInputMapRef();

			int GetPreviousInputState(int i);

			int GetPreviousMousePos(int i);

			void SetPreviousInputState(int i, int state);

			void SetPreviousMousePos( int i, int pos );
		protected:
			//TEinput specific
			InputMap		m_inputMap;

		};
	}
}

#endif