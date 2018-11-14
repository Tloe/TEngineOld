#ifndef TETEXTURELOADER_H
#define TETEXTURELOADER_H
#include <unordered_map>
#include <memory>
#include <stdint.h>

namespace TE
{
	namespace Resources
	{


		class TextureLoader
		{
		public:
			virtual TextureInfo LoadTexture(std::vector<uint8_t>& dataInOut) const = 0;
		};

		typedef std::shared_ptr<TextureLoader> TextureLoaderPtr;
	}
}

#endif