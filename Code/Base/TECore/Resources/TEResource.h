#ifndef TERESOURCE_H
#define TERESOURCE_H

#include "TEDataTypes.h"
#include <iosfwd>
#include <string>
#include <vector>

namespace TE {
    namespace IO {
        class FileIO;
    }
    namespace Resources {
        template <typename T>
        class CustomLoader;
    }

    namespace Resources {
        class Resource {
          public:
            typedef std::vector<U8>::iterator DataIterator;
            typedef std::vector<U8>::const_iterator ConstDataIterator;

            const std::string &GetFileExtention() const;
            const std::string &GetFilePath() const;
            void SetFilePath(const std::string &filePath);

          protected:
            Resource();
            Resource(const std::string &filePath);
            const U8 *GetDataFront() const;
            I32 GetDataSize() const;
            void SetData(DataIterator first, DataIterator last);
            virtual void Save(IO::FileIO &fileIO);
            virtual void Load(IO::FileIO &fileIO);
            virtual bool IsLoaded() const;
            virtual void Unload();

          private:
            std::vector<U8> m_data;
            std::string m_filePath;
            std::string m_fileExtention;
            U32 m_referenceCount;

            template <typename T>
            friend class ResourceManager;
            template <typename T>
            friend class ResourceHandle;
        };
    }
}

#endif
