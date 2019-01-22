#include "TEVertexBufferOpenGL.h"
#include "TEMesh.h"
#include "TEMappingOpenGL.h"

#include <assert.h>

TE::Render::APIVertexBuffer::APIVertexBuffer( const Mesh& mesh )
    : m_usageCount(1)
    , m_mesh(mesh)
{
	glGenBuffers(1, &m_glVBO);
	assert(glGetError() == GL_NO_ERROR);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_glVBO);
	assert(glGetError() == GL_NO_ERROR);
	
	VertexBufferInfo vertexBufferInfo = m_mesh.GetVertexBufferInfo();
	
	glBufferData(GL_ARRAY_BUFFER,
		vertexBufferInfo.dataSize,
		m_mesh.GetVertexBufferDataPtr(),
		APIMapping::s_usage[vertexBufferInfo.usage]);
	assert(glGetError() == GL_NO_ERROR);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	assert(glGetError() == GL_NO_ERROR);
}

TE::Render::APIVertexBuffer::~APIVertexBuffer()
{
	glDeleteBuffers(1, &m_glVBO);
	assert(glGetError() == GL_NO_ERROR);
}

void TE::Render::APIVertexBuffer::Enable()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_glVBO);
	assert(glGetError() == GL_NO_ERROR);
}

void TE::Render::APIVertexBuffer::Disable()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
    assert(glGetError() == GL_NO_ERROR);
}

U32 TE::Render::APIVertexBuffer::IncreaseUsageCount()
{
    return ++m_usageCount;
}

U32 TE::Render::APIVertexBuffer::DecreaseUsageCount()
{
    return --m_usageCount;
}
