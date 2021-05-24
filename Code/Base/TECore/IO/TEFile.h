#ifndef TEFILE_H
#define TEFILE_H

#include "TEDataTypes.h"
#include <fstream>
#include <memory>
#include <stdint.h>
#include <string>
#include <vector>

namespace TE::IO {
    class File {
      public:
        File();
        File(std::unique_ptr<std::fstream> fstream, const std::string &filePath);
        File(const std::string &filePath, const std::fstream::ios_base::openmode openMode);
        ~File();

        void Open(const std::string &filePath, const std::fstream::ios_base::openmode openMode);
        bool IsOpen();
        void ReadData(std::vector<U8> &data, std::streamoff offset = -1, I32 size = 0);
        void ReadData(U8 *data, std::streamoff offset = -1, I32 size = 0);
        void WriteData(const std::vector<U8> &data, std::streamoff offset = -1);
        void WriteData(const U8 *data, I32 size, std::streamoff offset = -1);
        void RemoveFileData(const std::string &filePath, std::streamoff offset, I32 deleteSize = 0);
        std::streamoff GetFileSize();
        void SetReadOffset(std::streamoff offset);
        void SetWriteOffset(std::streamoff offset);
        void ReadLine(std::string &line);

      private:
        std::unique_ptr<std::fstream> m_file;
        std::string m_filePath;
    };

    std::string FileExtentionFromPath(const std::string &filePath);
    std::string FileNameFromFullPath(const std::string &filePath);
    std::string FolderPathFromFilePath(const std::string &filePath);
}

#endif
