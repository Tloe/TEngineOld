#ifndef TEINPUTPROPERTIES_H
#define TEINPUTPROPERTIES_H

#include "TEProperty.h"

namespace TE
{
	namespace Input
	{
		namespace PropertyType
		{
			namespace InputAction
			{
				enum
				{
					AddForce,
					TransformPosition,
					TransformOrientation,
					TransformScale,
				};
			}
		}
		
		struct TransformPositionPropertyValues
		{
			TransformPositionPropertyValues(const Engine::Property& property);
			TransformPositionPropertyValues(Enum inputGroup,
				const std::string& inputString,
				Enum inputType,
				Bitmask inputStateFlags,
				const std::string& objectString,
				Enum actionType,
				F32 x,
				F32 y,
				F32 z);
			TransformPositionPropertyValues(Enum inputGroup,
				const std::string& inputString,
				Enum inputType,
				Bitmask inputStateFlags,
				Hash objectHash,
				Enum actionType,
				F32 x,
				F32 y,
				F32 z);

			Engine::Property GetProperty();

			Enum inputGroup;
			std::string inputString;
			Enum inputType;
			Bitmask inputStateFlags;
			Hash objectHash;
			Enum actionType;
			F32 x;
			F32 y;
			F32 z;
		};
	}
}

#endif