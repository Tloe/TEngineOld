#include <TEIndexBuffer.h>

TE::Render::IndexBuffer::IndexBuffer()
{

}

TE::Render::IndexBuffer::IndexBuffer( const std::string& filename, I32 usage /*= USAGE_STATIC*/ ) :
	Resource(filename),
	m_usage(usage)
{

}

unsigned TE::Render::IndexBuffer::GetDataSize() const
{
	return Resource::GetDataSize();
}

const U8* TE::Render::IndexBuffer::GetDataPtr() const
{
	return &GetData()[0];
}

const I16* TE::Render::IndexBuffer::GetDataShortPtr() const
{
	return reinterpret_cast<const I16*>(&GetData()[0]);
}

I32 TE::Render::IndexBuffer::GetElementCount() const
{
	return Resource::GetDataSize() / sizeof(I16);
}

I32 TE::Render::IndexBuffer::GetUsage() const
{
	return m_usage;
}

void TE::Render::IndexBuffer::SetUsage( I32 usage)
{
	m_usage = usage;
}
