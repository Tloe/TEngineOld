#ifndef TETEXTUREPNG_H
#define TETEXTUREPNG_H

#include "TETexture.h"

namespace TE
{
	namespace Render
	{
		class TexturePNG : public Texture
		{
		public:
			TexturePNG();
			TexturePNG(const std::string& filename);
			~TexturePNG();

			virtual void Prepare();
			virtual TextureInfo& GetTextureInfo();
		private:
			bool m_prepared;
			enum { SIGNATURE_LENGTH = 8 };
			TextureInfo m_textureInfo;
		};

	}
}

#endif