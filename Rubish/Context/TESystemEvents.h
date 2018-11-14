/**
 *	\file		TEInputEvents.h
 *  \author		Terje Loe
 *  \brief		Defenitions for Input event class ; will be changed when event system is changed to use fast delegates and command patterns
 */


#ifndef TESYSTEMEVENTS_H
#define TESYSTEMEVENTS_H

#include <TEEvent.h>

namespace TE
{
	namespace Context
	{
		enum
		{
			tekKeyboardEvent = 'keyb',
			tekMouseMoveEvent = 'mmov',
			tekMouseButtonEvent = 'mbut',
			tekAsciiInputEvent = 'asci',
			tekResizeEvent = 'rsiz'
		};

		class KeyboardEvent : public Events::Event
		{
		public:
			KeyboardEvent(I32 inputState, TEInput teInput )
				: Events::Event(tekKeyboardEvent), m_inputState(inputState), m_teInput(teInput)
			{}

			I32 InputState()
			{
				return m_inputState;
			}

			TEInput TeInput()
			{
				return m_teInput;
			}
		private:
			I32			m_inputState;
			TEInput		m_teInput;
		};

		class MouseMoveEvent : public Events::Event
		{
		public:
			MouseMoveEvent(I32 x, I32 y, I32 deltax, I32 deltay )
				: Events::Event(tekMouseMoveEvent), m_x(x), m_y(y), m_deltax(deltax), m_deltay(deltay)
			{}

			I32 X()
			{
				return m_x;
			}

			I32 Y()
			{
				return m_y;
			}

			I32 DeltaX()
			{
				return m_deltax;
			}

			I32 DeltaY()
			{
				return m_deltay;
			}
		private:
			I32 m_x;
			I32 m_y;
			I32 m_deltax;
			I32 m_deltay;
		};

		class MouseButtonEvent : public Events::Event
		{
		public:
			MouseButtonEvent(I32 inputState, TEInput teInput )
				: Events::Event(tekMouseButtonEvent), m_inputState(inputState), m_teInput(teInput)
			{}

			I32 InputState()
			{
				return m_inputState;
			}

			TEInput TeInput()
			{
				return m_teInput;
			}
		private:
			I32			m_inputState;
			TEInput		m_teInput;
		};

		class AsciiInputEvent : public Events::Event
		{
		public:
			AsciiInputEvent(char ascii)
				: Events::Event(tekAsciiInputEvent), m_ascii(ascii)
			{}

			char Ascii()
			{
				return m_ascii;
			}
		private:
			char m_ascii;
		};
		
		class WindowResizeEvent : public Events::Event
		{
		public:
			WindowResizeEvent(I32 width, I32 height)
				: 
				Events::Event(tekResizeEvent),
				m_width(width),
				m_height(height)
			{}

			I32 GetWidth()
			{
				return m_width;
			}
			
			I32 GetHeight()
			{
				return m_height;
			}
		private:
			I32 m_width;
			I32 m_height;
		};
	}
}

#endif
