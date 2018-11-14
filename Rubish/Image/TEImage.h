#ifndef TEIMAGE_H
#define TEIMAGE_H

#include "TEResource.h"

namespace TE
{
	namespace Images
	{


		class Image : public Resources::Resource
		{
		public:
			Image(const std::string& filename);
			virtual ~Image();
			virtual void Prepare() = 0;
			virtual ImageInfo& GetImageInfo() = 0;
			uint8_t* GetDataPtr();
		};

		typedef std::shared_ptr<Image> ImagePtr;
	}
}

#endif