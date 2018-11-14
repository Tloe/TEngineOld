#ifndef TETEXTURELOADERMANAGER_H
#define TETEXTURELOADERMANAGER_H

#include <unordered_map>
#include "TETextureLoader.h"
#include <string>

namespace TE
{
	namespace Resources
	{
		class TextureLoaderManager
		{
		public:
			typedef std::unordered_map<std::string, TextureLoaderPtr> TextureLoaders;
			const TextureLoader* GetTextureLoader( const std::string& fileExtention);
		private:
			TextureLoaders m_textureLoaders;
		};
	}
}

#endif