#include <TEProperty.h>

TE::Engine::Property::Property( U32 valueCount, Enum propertyType)
	:
	m_propertyType(propertyType)
{
	m_values.resize(valueCount);
}

Enum TE::Engine::Property::GetPropertyType() const
{
	return m_propertyType;
}

const TE::Core::Variant& TE::Engine::Property::operator[]( const U32 index ) const
{
	assert(index < m_values.size() && index >= 0);

	return m_values[index];
}

TE::Core::Variant& TE::Engine::Property::operator[]( const U32 index )
{
	assert(index < m_values.size() && index >= 0);

	return m_values[index];
}