#include <TEVertexShader.h>
#include "TEBufferLayout.h"

TE::Render::VertexShader::VertexShader(const std::string& filename, BufferLayoutPtr& bufferLayout)
	:
	Resource(filename),
	m_bufferLayout(bufferLayout)
{

}

const TE::Render::BufferLayoutPtr& TE::Render::VertexShader::GetBufferLayoutPtrRef() const
{
	return m_bufferLayout;
}

const char* TE::Render::VertexShader::GetDataPtr() const
{
	return reinterpret_cast<const char*>(&GetDataRef()[0]);
}

int TE::Render::VertexShader::GetDataSize() const
{
	return Resource::GetDataSize();
}
