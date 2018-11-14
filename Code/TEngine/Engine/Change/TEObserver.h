#ifndef TEOBSERVER_H
#define TEOBSERVER_H

#include "TEDataTypes.h"

#include <memory>

namespace TE
{
	namespace Engine { class Subject; }

	namespace Engine
	{
		class Observer
		{
		public:
			virtual ~Observer(){}
			virtual void OnSubjectChange(Subject* subject, Bitmask64 changeBits) = 0;
		};

		typedef std::unique_ptr<Observer> ObserverUPtr;
	}
}

#endif
