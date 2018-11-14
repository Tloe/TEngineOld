#ifndef TETEXTURELOADERPNG_H
#define TETEXTURELOADERPNG_H

#include "TETextureLoader.h"
#include <vector>
#include <stdint.h>

namespace TE
{
	namespace Resources
	{
		class TextureLoaderPNG : public TextureLoader
		{
		public:
			TextureLoaderPNG();

			virtual TextureInfo LoadTexture( std::vector<uint8_t>& dataInOut ) const;
		private:
			enum { SIGNATURE_LENGTH = 8 };
		};
	}
}

#endif