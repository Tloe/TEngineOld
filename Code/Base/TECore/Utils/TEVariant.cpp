#include <TEVariant.h>
#include <cstring>

TE::Core::Variant::Variant()
    : m_variantType(VariantType::NotSet)
{

}

TE::Core::Variant::~Variant()
{
    ClearString();
}

TE::Core::Variant::Variant(const Variant &other)
    : m_variantType(VariantType::NotSet)
{
    if(other.m_variantType == VariantType::String)
    {
        SetString(other.m_value.cString);
    }
    else
    {
        m_value = other.m_value;
        m_variantType = other.m_variantType;
    }
}

TE::Core::Variant::Variant(Variant &&other)
    : m_variantType(VariantType::NotSet)
{
    if(other.m_variantType == VariantType::String)
    {
        SetString(other.m_value.cString);
    }
    else
    {
        m_value = std::move(other.m_value);
        m_variantType = std::move(other.m_variantType);
    }
}

TE::Core::Variant &TE::Core::Variant::operator =(const TE::Core::Variant & other)
{
    if(other.m_variantType == VariantType::String)
    {
        SetString(other.m_value.cString);
    }
    else
    {
        m_value = other.m_value;
        m_variantType = other.m_variantType;
    }

    return *this;
}

TE::Core::Variant &TE::Core::Variant::operator =(TE::Core::Variant && other)
{
    if(other.m_variantType == VariantType::String)
    {
        SetString(other.m_value.cString);
    }
    else
    {
        m_value = std::move(other.m_value);
        m_variantType = std::move(other.m_variantType);
    }

    return *this;
}


TE::Core::Variant::Variant( const std::string & str )
{
    SetString(str.c_str());
}

TE::Core::Variant::Variant(const char *str )
{
    SetString(str);
}

TE::Core::Variant::Variant( I32 i32 )
	:
	m_variantType(VariantType::I32)
{
	m_value.i32 = i32;
}

TE::Core::Variant::Variant( U32 u32 )
	:
	m_variantType(VariantType::U32)
{
	m_value.u32 = u32;
}

TE::Core::Variant::Variant( bool boolean )
	:
    m_variantType(VariantType::BOOL)
{
	m_value.boolean = boolean;
}

TE::Core::Variant::Variant( F32 f32 )
	:
	m_variantType(VariantType::F32)
{
	m_value.f32 = f32;
}

TE::Core::VariantType TE::Core::Variant::GetType() const
{
	return m_variantType;
}

void TE::Core::Variant::SetString( const std::string& str )
{
    SetString(str.c_str());
}

void TE::Core::Variant::SetString(const char *str)
{
    ClearString();

    m_value.cString = new char[strlen(str) + 1];
    strcpy(m_value.cString, str);

    m_variantType = VariantType::String;
}

void TE::Core::Variant::SetI32( I32 i32)
{
	ClearString();

	m_value.i32 = i32;
	m_variantType = VariantType::I32;
}

void TE::Core::Variant::SetU32( U32 u32 )
{
	ClearString();

	m_value.u32 = u32;
	m_variantType = VariantType::U32;
}

void TE::Core::Variant::SetBool( bool boolean )
{
	ClearString();

	m_value.boolean = boolean;
    m_variantType = VariantType::BOOL;
}

void TE::Core::Variant::SetF32( F32 f32 )
{
	ClearString();

	m_value.f32 = f32;
	m_variantType = VariantType::F32;
}

I32 TE::Core::Variant::GetI32() const
{
	assert(m_variantType == VariantType::I32);

	return m_value.i32;
}

U32 TE::Core::Variant::GetU32() const
{
	assert(m_variantType == VariantType::U32);

	return m_value.u32;
}

bool TE::Core::Variant::GetBool() const
{
    assert(m_variantType == VariantType::BOOL);

	return m_value.boolean;
}

F32 TE::Core::Variant::GetF32() const
{
	assert(m_variantType == VariantType::F32);

	return m_value.f32;
}

std::string TE::Core::Variant::GetString() const
{
	assert(m_variantType == VariantType::String);

	return std::string(m_value.cString);
}

const char* TE::Core::Variant::GetCString() const
{
	assert(m_variantType == VariantType::String);

	return m_value.cString;
}

void TE::Core::Variant::ClearString()
{
	if (m_variantType == VariantType::String)
	{
		delete[] m_value.cString;
		m_variantType = VariantType::NotSet;
	}
}
