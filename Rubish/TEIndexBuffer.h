#ifndef TEINDEXBUFFER_H
#define TEINDEXBUFFER_H

#include <TEResource.h>
#include <string>

namespace TE
{
	namespace Render
	{
		class IndexBuffer : public Resources::Resource
		{
		public:
			enum
			{
				USAGE_STATIC,	//The data store contents will be modified once and used many times.
				USAGE_DYNAMIC,	//The data store contents will be modified repeatedly and used many times.
			};

			IndexBuffer();
			IndexBuffer(const std::string& filename, I32 usage = USAGE_STATIC);

			void SetUsage(I32 usage);
			unsigned GetDataSize() const;
			const U8* GetDataPtr() const;
			const I16* GetDataShortPtr() const;
			I32 GetElementCount() const;
			I32 GetUsage() const;
						
			//friend bool operator<(const IndexBuffer& lhs, const IndexBuffer& rhs);
		private:
			I32 m_usage;
		};
		
		/*bool operator<(const IndexBuffer& lhs, const IndexBuffer& rhs)
		{
			return &lhs < &rhs;
		}*/
	}
}

#endif
