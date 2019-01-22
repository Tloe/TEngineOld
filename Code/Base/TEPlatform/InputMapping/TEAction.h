#ifndef TEACTION_H
#define TEACTION_H

#include "TEDataTypes.h"

namespace TE
{
	namespace InputMapping
	{
		struct Action
		{
			std::string name;
			Hash nameHash;
			Enum defaultKey;
			Enum userKey;
		};
	}
}

#endif