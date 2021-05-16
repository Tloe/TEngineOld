#include "TEIndexBufferOpenGL.h"
#include "TEMappingOpenGL.h"
#include "TEMesh.h"

#include <assert.h>

TE::Render::APIIndexBuffer::APIIndexBuffer(const Mesh &mesh)
    : m_usageCount(1),
      m_mesh(mesh) {
    glGenBuffers(1, &m_glIBO);
    assert(glGetError() == GL_NO_ERROR);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_glIBO);
    assert(glGetError() == GL_NO_ERROR);

    IndexBufferInfo indexBufferInfo = m_mesh.GetIndexBufferInfo();

    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 indexBufferInfo.dataSize,
                 m_mesh.GetIndexBufferDataPtr(),
                 APIMapping::s_usage[indexBufferInfo.usage]);
    assert(glGetError() == GL_NO_ERROR);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    assert(glGetError() == GL_NO_ERROR);
}

TE::Render::APIIndexBuffer::~APIIndexBuffer() {
    glDeleteBuffers(1, &m_glIBO);
    assert(glGetError() == GL_NO_ERROR);
}

void TE::Render::APIIndexBuffer::Enable() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_glIBO);
    assert(glGetError() == GL_NO_ERROR);
}

void TE::Render::APIIndexBuffer::Disable() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    assert(glGetError() == GL_NO_ERROR);
}

U32 TE::Render::APIIndexBuffer::IncreaseUsageCount() {
    return ++m_usageCount;
}

U32 TE::Render::APIIndexBuffer::DecreaseUsageCount() {
    return ++m_usageCount;
}
