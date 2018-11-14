#ifndef TEIMAGEPNG_H
#define TEIMAGEPNG_H

#include "TEImage.h"

namespace TE
{
	namespace Images
	{
		class ImagePNG : public Image
		{
		public:
			ImagePNG(const std::string& filename);
			~ImagePNG();

			void Prepare();
			ImageInfo& GetImageInfo();
		private:

			ImageInfo m_imageInfo;
		};
	}
}

#endif