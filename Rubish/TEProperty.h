#ifndef TEPROPERTY_H
#define TEPROPERTY_H

#include <TEDataTypes.h>
#include <TEVariant.h>

#include <vector>

namespace TE
{
	namespace Engine
	{
		class Property
		{
		public:
			Property(U32 valueCount, Enum propertyType);

			Enum GetPropertyType() const;
			const Core::Variant& operator[](const U32 index) const;
			Core::Variant& operator[](const U32 index);

		private:
			Enum m_propertyType;
			std::vector<Core::Variant> m_values;
		};
		
		typedef std::vector<Property> PropertyVec;
	}
}

#endif