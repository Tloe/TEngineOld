#ifndef TEFILESYSTEMIO_H
#define TEFILESYSTEMIO_H

#include "TEFileIO.h"

namespace TE::IO {
    class FileSystemIO : public FileIO {
      public:
        FileSystemIO(const std::string &rootPath = "");
        void SetRootPath(const std::string &rootPath);

        void LoadFile(const std::string &filePath, std::vector<U8> &data);
        void LoadFile(I32 fileHash, std::vector<U8> &data);
        void SaveFile(const std::string &filePath, const std::vector<U8> &data);
        void SaveFile(I32 fileHash, const std::vector<U8> &data);
        bool SupportsHash();

      private:
        std::string m_rootPath;
    };
}

#endif
