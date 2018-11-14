#ifndef TESCENECHANGE_H
#define TESCENECHANGE_H

#include "TEDataTypes.h"
#include "TEValue.h"

namespace TE
{
	namespace Engine
	{
		struct CreateObjectData
		{
			std::string objectName;
			std::vector<U32> systemIds;
			std::vector<std::string> objectTypes;
			std::vector<Core::Value> values;

		};

		class SceneChange
		{
		public:
			virtual const CreateObjectData GetCreateObjectData() = 0;
		};
	}
}

#endif
