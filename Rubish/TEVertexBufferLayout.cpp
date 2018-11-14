#include <TEVertexBufferLayout.h>
#include <assert.h>

TE::Render::VertexBufferLayout::LayoutElement::LayoutElement( I32 layoutSemantic, I32 valueType, I32 valueCount,I32 byteOffset )
	:
	layoutSemantic(layoutSemantic),
	valueType(valueType),
	valueCount(valueCount),
	byteOffset(byteOffset)
{

}

TE::Render::VertexBufferLayout::LayoutElement::LayoutElement()
{

}


TE::Render::VertexBufferLayout::VertexBufferLayout()
{

}

TE::Render::VertexBufferLayout::VertexBufferLayout(const std::string& filename)
	:
	Resource(filename)
{

}

void TE::Render::VertexBufferLayout::AddElement( I32 layoutSemantic,I32 valueType, I32 valueCount, I32 byteOffset )
{
	LayoutElement newLayout(layoutSemantic, valueType, valueCount, byteOffset); 
	m_elements.push_back(newLayout);
}

I32 TE::Render::VertexBufferLayout::GetElementCount() const
{
	return m_elements.size();
}

void TE::Render::VertexBufferLayout::GetElement( unsigned index, LayoutElement& element ) const
{
	assert(index < m_elements.size());
	element = m_elements[index];
}
