#ifndef TEFILELOADER_H
#define TEFILELOADER_H
#include <stdint.h>
#include <string>
#include <vector>

namespace TE {
namespace IO {
    class FileLoader {
      public:
        virtual ~FileLoader();
        virtual void LoadFile(const std::string &filePath, std::vector<uint8_t> &data)       = 0;
        virtual void LoadFile(int fileHash, std::vector<uint8_t> &data)                      = 0;
        virtual void SaveFile(const std::string &filePath, const std::vector<uint8_t> &data) = 0;
        virtual void SaveFile(int fileHash, const std::vector<uint8_t> &data)                = 0;
    };

    typedef std::shared_ptr<FileLoader> FileLoaderPtr;
}
}

#endif