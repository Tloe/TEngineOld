#ifndef TEIMAGE_H
#define TEIMAGE_H

#include "TEDataTypes.h"
#include <memory>
#include <string>

namespace TE {
    namespace IO {
        class FileIO;
    }

    namespace Images {
        namespace ColorType {
            enum {
                RGB,
                RGBA
            };
        }

        class Image {
          public:
            virtual ~Image(){};
            virtual void Load(IO::FileIO &fileIO, const std::string &filePath) = 0;
            virtual void Unload()                                              = 0;
            virtual bool IsLoaded()                                            = 0;
            virtual void Prepare()                                             = 0;
            virtual U8 *GetDataPtr()                                           = 0;
            virtual U32 GetDataSize()                                          = 0;
            virtual U32 GetWidth()                                             = 0;
            virtual U32 GetHeight()                                            = 0;
            virtual U32 GetBitDepth()                                          = 0;
            virtual U32 GetColorType()                                         = 0;
        };

        typedef std::unique_ptr<Image> ImageUPtr;
    }
}

#endif
