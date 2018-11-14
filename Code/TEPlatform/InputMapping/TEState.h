#ifndef TESTATE_H
#define TESTATE_H

#include "TEDataTypes.h"

namespace TE
{
	namespace InputMapping
	{
		struct State
		{
			std::string name;
			Hash nameHash;
			Enum defaultKey;
			Enum userKey;
		};
	}
}

#endif