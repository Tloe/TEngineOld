#ifndef TEPIXELSHADER_H
#define TEPIXELSHADER_H

#include <TEResource.h>
#include <memory>
#include <string>
#include <vector>
#include <stdint.h>

namespace TE
{
	//Forward declarations
	namespace Render { class BufferLayout; }
	//End forward declarations

	namespace Render
	{
		class PixelShader : public Resources::Resource
		{
		public:
			PixelShader(const std::string& filename)
				:
				Resource(filename)
			{}

			const char* GetDataPtr() const
			{
				return reinterpret_cast<const char*>(&GetDataRef()[0]);
			}

			int GetDataSize() const
			{
				return Resource::GetDataSize();
			}
		};

		typedef std::shared_ptr<PixelShader> PixelShaderPtr;
	}
}

#endif
