#ifndef TEDATFILE_H
#define TEDATFILE_H

#include "TEFile.h"

#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include <stdint.h>

namespace TE::Resources {
  class Crypto;
  using CryptoUPtr = std::unique_ptr<Crypto>;
}

namespace TE::IO {
  class DatPath;

  using StringHash            = std::size_t;
  using SizeOffsetPair        = std::pair<I32, I32>;
  using DatFileIndexHashMap   = std::unordered_map<StringHash, SizeOffsetPair>;
  using StringSizeOffsetPair  = std::pair<std::string, SizeOffsetPair>;
  using DatFileIndexStringMap = std::map<std::string, SizeOffsetPair>;

  class DatFile {
  public:
    DatFile();
    DatFile(Resources::CryptoUPtr &crypto);
    ~DatFile();

    bool OpenFile(const std::string &filePath);
    bool GetFileData(StringHash filehash, std::vector<U8> &dataOut);
    bool GetFileData(const std::string &filePath, std::vector<U8> &dataOut);

    // Adding and removing folders should only be done in tools
    bool AddFile(const std::string &filePath, const DatPath &datPath);
    bool AddFile(std::vector<U8> &data, const DatPath &datPath);
    bool NewFolder(const DatPath &datPath);
    void RemovePath(const DatPath &datPath);
    I32 GetFolderContent(const DatPath &datPath, std::vector<std::string> &foldersAndFiles);

  private:
    DatFileIndexStringMap m_fileIndexString;
    DatFileIndexHashMap m_fileIndexHash;
    U32 m_indexOffset;
    File m_datFile;
    std::string m_filePath;
    Resources::CryptoUPtr m_crypto;
    bool m_emptyFile;
    void ActivateIndexStringMap();
    void RemoveFolder(const DatPath &datPath);
    void RemoveFile(const DatPath &datPath);
    void UpdateIndexOffsets();
  };

  I32 ReadDatIndexHash(File &file, DatFileIndexHashMap &fileIndex);
  I32 ReadDatIndexString(File &file, DatFileIndexStringMap &fileIndex);
  void WriteDatIndex(File &file, DatFileIndexStringMap &fileIndex, U32 offset);
  template <typename KeyT, typename MapT>
  void SortedIndex(std::vector<std::pair<KeyT, SizeOffsetPair>> &sorted, MapT &map) {
    sorted.insert(sorted.end(), map.begin(), map.end());

    /*struct SortByOffset : public std::binary_function<std::pair<KeyT, SizeOffsetPair>,
                                                                                             std::pair<KeyT,
    SizeOffsetPair>, bool>
    {
            bool operator()(const std::pair<KeyT, SizeOffsetPair>& lhs,
                                            const std::pair<KeyT, SizeOffsetPair>& rhs)
    const
            {
                    return lhs.second.second < rhs.second.second;
            }
    };*/
    sort(sorted.begin(), sorted.end(),
         [](auto &lhs, auto &rhs) -> bool { return lhs.second.second < rhs.second.second; });
  }
}

#endif
