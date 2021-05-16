#ifndef TEIMAGEPNG_H
#define TEIMAGEPNG_H

#include "TEDataTypes.h"
#include "TEImage.h"

#include <vector>

namespace TE {
namespace Images {
    class ImagePng : public Image {
      public:
        ImagePng();

        virtual void Load(IO::FileIO &fileIO, const std::string &filePath);
        virtual void Unload();
        virtual bool IsLoaded();
        virtual void Prepare();
        virtual U8 *GetDataPtr();
        virtual U32 GetDataSize();
        virtual U32 GetWidth();
        virtual U32 GetHeight();
        virtual U32 GetBitDepth();
        virtual U32 GetColorType();

      private:
        enum {
            SIGNATURE_LENGTH = 8
        };

        std::vector<U8> m_filedata;
        bool m_prepared;
        U32 m_width;
        U32 m_height;
        U32 m_bitDepth;
        U32 m_colorType;
    };
}
}

#endif
