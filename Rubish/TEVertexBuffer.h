#ifndef TEVERTEXBUFFER_H
#define TEVERTEXBUFFER_H

#include <TEResource.h>
#include <stdint.h>
#include "TEDataTypes.h"

namespace TE
{
	namespace Render
	{
		class VertexBuffer : public Resources::Resource
		{
		public:
			enum
			{
				PRIMITIVETYPE_POINTS,
				PRIMITIVETYPE_LINES,
				PRIMITIVETYPE_LINE_STRIP,
				PRIMITIVETYPE_TRIANGLES,
				PRIMITIVETYPE_TRIANGLE_STRIP,
				PRIMITIVETYPE_COUNT
			};

			enum
			{
				USAGE_STATIC,	//The data store contents will be modified once and used many times.
				USAGE_DYNAMIC,	//The data store contents will be modified repeatedly and used many times.
			};

			VertexBuffer();
			VertexBuffer(const std::string& filename,I32 primitiveType = PRIMITIVETYPE_POINTS, I32 usage = USAGE_STATIC);

			I32 GetPrimitiveType() const;
			I32 GetElementCount() const;
			unsigned GetDataSize() const;
			const U8* GetDataPtr() const;
			const F32* GetDataF32Ptr() const;
			unsigned GetElementSize() const;
			I32 GetUsage() const;
			void SetPrimitiveType(I32 primitiveType);
			void SetUsage(I32 usage);

			//friend bool operator<(const VertexBuffer& lhs, const VertexBuffer& rhs);
		private:
			I32 m_primitiveType;
			I32 m_usage;
		};

		/*bool operator<(const VertexBuffer& lhs, const VertexBuffer& rhs)
		{
			return &lhs < &rhs;
		}*/
	}
}

#endif
