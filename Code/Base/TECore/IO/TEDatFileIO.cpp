#include <TEDatFileIO.h>
#include <assert.h>

TE::IO::DatFileIO::DatFileIO(const std::string &datFilePath) : m_datFilePath(datFilePath) {
    m_datFile.OpenFile(m_datFilePath);
}

void TE::IO::DatFileIO::LoadFile(const std::string &filePath, std::vector<U8> &data) {
    m_datFile.GetFileData(filePath, data);
}

void TE::IO::DatFileIO::LoadFile(I32 fileHash, std::vector<U8> &data) {
    // Not implemented. DatFile class should probably be rewritten to not use hashes at all? Atleast
    // resource manager doesnt use it anymore Resources arent loaded too often so string lookup is
    // fast enough
}

TE::IO::DatFile &TE::IO::DatFileIO::GetDatFile() { return m_datFile; }

void TE::IO::DatFileIO::SaveFile(const std::string &filePath, const std::vector<U8> &data) {
    assert("Not implemented");
}

void TE::IO::DatFileIO::SaveFile(I32 fileHash, const std::vector<U8> &data) {
    assert("Not implemented");
}

bool TE::IO::DatFileIO::SupportsHash() { return true; }
