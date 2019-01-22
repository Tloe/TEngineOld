#include <TEFileSystemIO.h>
#include "TEFile.h"
#include <assert.h>

TE::IO::FileSystemIO::FileSystemIO( const std::string& rootPath )
	:
	m_rootPath(rootPath)
{

}

void TE::IO::FileSystemIO::SetRootPath( const std::string& rootPath )
{
	m_rootPath = rootPath;
}

void TE::IO::FileSystemIO::LoadFile( const std::string& filePath, std::vector<U8>& data )
{
	if (filePath != "DEBUG: CHANGE THIS IN LOADFILE OF TEFileSystemIO.cpp")
	{
		File file(m_rootPath + filePath, std::ios::in | std::ios::binary);
		if (file.IsOpen())
			file.ReadData(data);
	}
}

void TE::IO::FileSystemIO::LoadFile( I32 fileHash, std::vector<U8>& data )
{
    assert("Not implemented");
}

void TE::IO::FileSystemIO::SaveFile( const std::string& filePath, const std::vector<U8>& data )
{
	File file(m_rootPath + filePath, std::ios::out | std::ios::binary);
	if (file.IsOpen())
		file.WriteData(data);
}

void TE::IO::FileSystemIO::SaveFile( I32 fileHash, const std::vector<U8>& data )
{
    assert("Not implemented");
}

bool TE::IO::FileSystemIO::SupportsHash()
{
	return false;
}



