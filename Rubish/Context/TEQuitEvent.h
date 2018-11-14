#ifndef TEQUITEVENT_H
#define TEQUITEVENT_H

#include <TEEvent.h>

namespace TE
{
	namespace Context
	{
		enum
		{
			tekQuitEvent = 'quit'
		};

		class QuitEvent : public Events::Event
		{
		public:
			QuitEvent()
				: Events::Event(tekQuitEvent)
			{}
		};
	}
}

#endif