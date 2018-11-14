#include <TETextureLoaderManager.h>
#include "TETextureLoaderPNG.h"
#include <assert.h>

const TE::Resources::TextureLoader* TE::Resources::TextureLoaderManager::GetTextureLoader( const std::string& fileExtention )
{
	TextureLoaders::iterator findItr = m_textureLoaders.find(fileExtention);
	if(findItr != m_textureLoaders.end())
	{
		return findItr->second.get();
	}

	if(fileExtention.compare("png") == 0)
	{
		TextureLoaderPtr newPngLoader(new TE::Resources::TextureLoaderPNG);
		m_textureLoaders.insert(std::make_pair(fileExtention, newPngLoader));
		return newPngLoader.get();
	}

	return NULL;
}
