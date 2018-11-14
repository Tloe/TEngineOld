#ifndef TEEVENTHANDLER_H
#define TEEVENTHANDLER_H

#include "TEDataTypes.h"

namespace TE
{
	namespace Event { class EventVisitor; }
	namespace Event { class ResolutionEvent; }
	namespace Event { class TranslationEvent; }
    namespace Event { class ScaleEvent; }
    namespace Event { class OrientationEvent; }
    namespace Event { class EnvironmentUpdateEvent; }

	namespace Event
	{
		class EventHandler
		{
		public:
            virtual void HandleEvent(EventVisitor&);
            virtual void HandleEvent(ResolutionEvent&);
            virtual void HandleEvent(TranslationEvent&);
            virtual void HandleEvent(ScaleEvent&);
            virtual void HandleEvent(OrientationEvent&);
            virtual void HandleEvent(EnvironmentUpdateEvent&);
		};
	}
}

#endif
