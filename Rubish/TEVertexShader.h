#ifndef TEVERTEXSHADER_H
#define TEVERTEXSHADER_H

#include <TEResource.h>
#include <memory>
#include <string>
#include "TEBufferLayout.h"
#include <vector>
#include <stdint.h>

namespace TE
{
	namespace Render
	{
		class VertexShader : public Resources::Resource
		{
		public:
			VertexShader(const std::string& filename, BufferLayoutPtr& bufferLayout);

			const std::vector<uint8_t>& GetDataRef() const
			{
				return Resource::GetDataRef();
			}
			const char* GetDataPtr() const;
			int GetDataSize() const;
			const BufferLayoutPtr& GetBufferLayoutPtrRef() const;
		private:
			BufferLayoutPtr m_bufferLayout;
		};

		typedef std::shared_ptr<VertexShader> VertexShaderPtr;
	}
}

#endif
