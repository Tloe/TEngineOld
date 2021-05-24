#include <TEFile.h>
#include <algorithm>
#include <assert.h>
#include <fstream>
#include <iostream>
#include <string>

TE::IO::File::File() {}

TE::IO::File::File(std::unique_ptr<std::fstream> fstream, const std::string &filePath)
    : m_file(std::move(fstream)),
      m_filePath(filePath) {
    assert(m_file->is_open() && "File not open.");
}

TE::IO::File::File(const std::string &filePath, const std::fstream::ios_base::openmode openMode)
    : m_file(new std::fstream(filePath, openMode)),
      m_filePath(filePath) {}

void TE::IO::File::ReadData(std::vector<U8> &data,
                            std::streamoff offset /*= -1*/,
                            I32 size /*= 0*/) {
    if (size == 0) {
        I32 oldOffset = static_cast<I32>(m_file->tellg());
        m_file->seekg(0, std::ios::end);
        size = static_cast<I32>(m_file->tellg());

        if (offset == -1)
            m_file->seekg(oldOffset, std::ios::beg);
    }

    if (offset >= 0)
        m_file->seekg(offset, std::ios::beg);

    data.resize(size);
    m_file->read(reinterpret_cast<char *>(&data[0]), size);
}

void TE::IO::File::ReadData(U8 *data, std::streamoff offset /*= -1*/, I32 size /*= 0*/) {
    if (size == 0) {
        I32 oldOffset = static_cast<I32>(m_file->tellg());
        m_file->seekg(0, std::ios::end);
        size = static_cast<I32>(m_file->tellg() - offset);

        if (offset == -1)
            m_file->seekg(oldOffset, std::ios::end);
    }

    if (offset >= 0)
        m_file->seekg(offset, std::ios::beg);

    m_file->read(reinterpret_cast<char *>(data), size);
}

void TE::IO::File::WriteData(const std::vector<U8> &data, std::streamoff offset /*= -1*/) {
    if (offset >= 0)
        m_file->seekp(offset, std::ios::beg);

    m_file->write(reinterpret_cast<const char *>(&data[0]), data.size());
}

void TE::IO::File::WriteData(const U8 *data, I32 size, std::streamoff offset /*= -1*/) {
    if (offset >= 0)
        m_file->seekp(offset, std::ios::beg);

    m_file->write(reinterpret_cast<const char *>(data), size);
}

void TE::IO::File::RemoveFileData(const std::string &filePath,
                                  std::streamoff offset,
                                  I32 deleteSize /*= 0*/) {
    std::ofstream tempFile("!temp!", std::ios::out | std::ios::binary | std::ios::trunc);

    m_file->seekg(0, std::ios::end);
    I32 totalsize = static_cast<I32>(m_file->tellg());
    m_file->seekg(0, std::ios::beg);

    if (deleteSize == 0)
        deleteSize = totalsize - static_cast<I32>(offset);

    I32 bufferSize = 1024;
    std::vector<U8> buffer(bufferSize);

    std::streamoff currentOffset = 0;
    bool notDeleted              = true;
    I32 readSize;
    while (currentOffset != totalsize) {
        if (notDeleted) {
            if (bufferSize > offset - currentOffset) {
                readSize = static_cast<I32>(offset - currentOffset);
                if (readSize)
                    m_file->read(reinterpret_cast<char *>(&buffer[0]), readSize);
                notDeleted    = false;
                currentOffset = offset + deleteSize;
                m_file->seekg(currentOffset, std::ios::beg);
            } else {
                readSize = bufferSize;
                m_file->read(reinterpret_cast<char *>(&buffer[0]), readSize);
                currentOffset += readSize;
            }
        } else {
            readSize = std::min<I32>(bufferSize, totalsize - static_cast<I32>(currentOffset));
            m_file->read(reinterpret_cast<char *>(&buffer[0]), readSize);
            currentOffset += readSize;
        }
        if (readSize)
            tempFile.write(reinterpret_cast<char *>(&buffer[0]), readSize);
    }
    tempFile.close();

    m_file->close();
    remove(filePath.c_str());
    rename("!temp!", filePath.c_str());
    m_file->open(filePath, std::ios::binary | std::ios::in | std::ios::out);
}

TE::IO::File::~File() { m_file->close(); }

void TE::IO::File::Open(const std::string &filePath,
                        const std::fstream::ios_base::openmode openMode) {
    if (m_file)
        m_file->close();

    m_file.reset(new std::fstream(filePath, openMode));
}

bool TE::IO::File::IsOpen() { return m_file && m_file->is_open(); }

std::streamoff TE::IO::File::GetFileSize() {
    m_file->seekg(0, std::ios::end);
    return m_file->tellg();
}

void TE::IO::File::SetReadOffset(std::streamoff offset) { m_file->seekg(offset, std::ios::beg); }

void TE::IO::File::ReadLine(std::string &line) { getline(*m_file, line); }

void TE::IO::File::SetWriteOffset(std::streamoff offset) { m_file->seekp(offset, std::ios::beg); }

std::string TE::IO::FileExtentionFromPath(const std::string &filePath) {
    size_t pos                = filePath.find_last_of('.');
    std::string fileExtention = filePath.substr(pos + 1);
    for (unsigned i = 0; i < fileExtention.size(); ++i)
        fileExtention[i] = tolower(fileExtention[i]);

    return fileExtention;
}

std::string TE::IO::FileNameFromFullPath(const std::string &filePath) {
    size_t pos           = filePath.find_last_of('/');
    std::string fileName = filePath.substr(pos + 1);

    return fileName;
}

std::string TE::IO::FolderPathFromFilePath(const std::string &filePath) {
    size_t pos             = filePath.find_last_of('/');
    std::string folderName = filePath.substr(0, pos);

    return folderName;
}
