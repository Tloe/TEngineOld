#ifndef TETEXTURE_H
#define TETEXTURE_H

#include <TEResource.h>
#include <unordered_map>
#include <string>
#include <TEImage.h>

namespace TE
{
	namespace Render
	{
		class Texture : public Resources::Resource
		{
		public:
			Texture(const std::string& filePath);
			Texture(const Texture&& other);
			virtual ~Texture();
			Texture& operator=(const Texture& rhs);

			virtual void Load(IO::FileIO& fileIO);
			virtual void Unload();
			virtual bool IsLoaded() const;
			void Prepare();
			Images::Image& GetImage();

		private:
			mutable Images::ImageUPtr m_image;
		};
	}
}

#endif