#ifndef TEINPUTMAPPER_H
#define TEINPUTMAPPER_H

#include <string>
#include <unordered_map>
#include "TEDataTypes.h"

namespace TE
{
	namespace Input
	{


		class InputMapper
		{
		public:
			
						
			virtual ~InputMapper();
			virtual const InputMapping& GetInputMapping(Enum teInput) = 0;
			virtual void SetMapping(Enum teInput, const std::string& objectName, const std::string& actionName) = 0;
		};
	}
}

#endif