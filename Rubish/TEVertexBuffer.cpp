#include <TEVertexBuffer.h>

TE::Render::VertexBuffer::VertexBuffer()
{

}

TE::Render::VertexBuffer::VertexBuffer( const std::string& filename,I32 primitiveType /*= PRIMITIVETYPE_POINTS*/, I32 usage /*= USAGE_STATIC*/ )
	:
	Resource(filename),
	m_primitiveType(primitiveType),
	m_usage(usage)
{

}

I32 TE::Render::VertexBuffer::GetPrimitiveType() const
{
	return m_primitiveType;
}

I32 TE::Render::VertexBuffer::GetElementCount() const
{
	return GetDataSize() / sizeof(F32);
}

unsigned TE::Render::VertexBuffer::GetDataSize() const
{
	return Resource::GetDataSize();
}

const U8* TE::Render::VertexBuffer::GetDataPtr() const
{
	return &GetData()[0];
}

const F32* TE::Render::VertexBuffer::GetDataF32Ptr() const
{
	return reinterpret_cast<const F32*>(&GetData()[0]);
}

unsigned TE::Render::VertexBuffer::GetElementSize() const
{
	return sizeof(F32);
}

I32 TE::Render::VertexBuffer::GetUsage() const
{
	return m_usage;
}

void TE::Render::VertexBuffer::SetPrimitiveType( I32 primitiveType )
{
	m_primitiveType = primitiveType;
}

void TE::Render::VertexBuffer::SetUsage( I32 usage )
{
	m_usage = usage;
}

