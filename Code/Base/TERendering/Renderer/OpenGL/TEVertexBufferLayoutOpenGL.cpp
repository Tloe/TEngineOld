#include "TEEffect.h"
#include "TEMappingOpenGL.h"
#include "TEMesh.h"
#include <TEVertexBufferLayoutOpenGL.h>

TE::Render::APIVertexBufferLayout::APIVertexBufferLayout(const Render::Mesh &mesh, const Render::Effect &effect)
    : m_usageCount(1),
      m_stride(0),
      m_hasPosition(false),
      m_hasNormals(false) {
    VertexBufferInfo::LayoutElementVec layoutElements = mesh.GetVertexBufferInfo().layoutElements;
    for (unsigned i = 0; i < layoutElements.size(); ++i) {
        if (layoutElements[i].layoutSemantic == Semantics::POSITION) {
            m_hasPosition        = true;
            m_positionValueCount = layoutElements[i].valueCount;
            m_positionValueType  = APIMapping::s_dataType[layoutElements[i].valueType];
            m_positionOffset     = layoutElements[i].byteOffset;
        } else if (layoutElements[i].layoutSemantic == Semantics::NORMAL) {
            m_hasNormals       = true;
            m_normalValueCount = layoutElements[i].valueCount;
            m_normalValueType  = APIMapping::s_dataType[layoutElements[i].valueType];
            m_normalOffset     = layoutElements[i].byteOffset;
        } else if (layoutElements[i].layoutSemantic >= Semantics::TEXTURE0 && layoutElements[i].layoutSemantic <= Semantics::TEXTURE7) {
            m_textureValueCount.push_back(layoutElements[i].valueCount);
            m_textureValueType.push_back(APIMapping::s_dataType[layoutElements[i].valueType]);
            m_textureOffset.push_back(layoutElements[i].byteOffset);
        }

        m_stride += layoutElements[i].byteOffset;
    }
    m_stride -= 4;
    m_textureCount = m_textureValueCount.size();

    glGenVertexArrays(1, &m_glVAO);
    assert(glGetError() == GL_NO_ERROR);
    glBindVertexArray(m_glVAO);
    assert(glGetError() == GL_NO_ERROR);

    if (m_hasPosition) {
        glEnableVertexAttribArray(APIMapping::s_semantics[Semantics::POSITION]);
        assert(glGetError() == GL_NO_ERROR);
        glVertexAttribPointer(APIMapping::s_semantics[Semantics::POSITION],
                              m_positionValueCount,
                              m_positionValueType,
                              GL_FALSE,
                              m_stride,
                              reinterpret_cast<void *>(m_positionOffset));
        assert(glGetError() == GL_NO_ERROR);
    }
    if (m_hasNormals) {
        glEnableVertexAttribArray(APIMapping::s_semantics[Semantics::NORMAL]);
        assert(glGetError() == GL_NO_ERROR);
        glVertexAttribPointer(APIMapping::s_semantics[Semantics::NORMAL],
                              m_normalValueCount,
                              m_normalValueType,
                              GL_FALSE, m_stride,
                              reinterpret_cast<void *>(m_normalOffset));
        assert(glGetError() == GL_NO_ERROR);
    }
    for (unsigned i = 0; i < m_textureCount; ++i) {
        glEnableVertexAttribArray(APIMapping::s_semantics[Semantics::TEXTURE0] + i);
        assert(glGetError() == GL_NO_ERROR);
        glVertexAttribPointer(APIMapping::s_semantics[Semantics::TEXTURE0] + i,
                              m_textureValueCount[i],
                              m_textureValueType[i],
                              GL_FALSE,
                              m_stride,
                              reinterpret_cast<void *>(m_textureOffset[i]));
        assert(glGetError() == GL_NO_ERROR);
    }

    glBindVertexArray(0);
    assert(glGetError() == GL_NO_ERROR);
}

TE::Render::APIVertexBufferLayout::~APIVertexBufferLayout() {
}

void TE::Render::APIVertexBufferLayout::Enable() {
    glBindVertexArray(m_glVAO);
    assert(glGetError() == GL_NO_ERROR);
}

void TE::Render::APIVertexBufferLayout::Disable() {
    glBindVertexArray(0);
    assert(glGetError() == GL_NO_ERROR);
}

U32 TE::Render::APIVertexBufferLayout::IncreaseUsageCount() {
    return ++m_usageCount;
}

U32 TE::Render::APIVertexBufferLayout::DecreaseUsageCount() {
    return --m_usageCount;
}
