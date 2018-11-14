#ifndef TEVERTEXBUFFERLAYOUT_H
#define TEVERTEXBUFFERLAYOUT_H

#include <TEResource.h>
#include <vector>

namespace TE
{
	namespace Render
	{
		class VertexBufferLayout : public Resources::Resource
		{
		public:
			struct LayoutElement
			{
				LayoutElement();
				LayoutElement(I32 layoutSemantic, I32 valueType, I32 valueCount,I32 byteOffset);

				I32 layoutSemantic;
				I32 valueType;
				I32 valueCount;
				I32 byteOffset;
			};

			enum
			{
				SEMANTIC_POSITION,
				SEMANTIC_COLOR,
				SEMANTIC_TEXTURE,
				SEMANTIC_NORMAL,
				SEMANTIC_COUNT
			};

			enum
			{
				TYPE_F32 = 0,
				TYPE_SHORT = 4,
				TYPE_COUNT
			};

			VertexBufferLayout();
			VertexBufferLayout(const std::string& filename);
			void AddElement(I32 layoutSemantic,I32 valueType, I32 valueCount, I32 byteOffset);
			void GetElement(unsigned index, LayoutElement& element) const;
			I32 GetElementCount() const;

			//friend bool operator<(VertexBufferLayout& lhs, VertexBufferLayout& rhs);
		private:
			std::vector<LayoutElement> m_elements;
		};

		/*bool operator<(VertexBufferLayout& lhs, VertexBufferLayout& rhs)
		{
			return &lhs < &rhs;
		}*/
	}
}

#endif

