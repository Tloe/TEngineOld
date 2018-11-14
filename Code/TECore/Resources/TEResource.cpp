#include <TEResource.h>
#include <TEFileIO.h>
#include <istream>
#include <assert.h>
#include <functional>
#include "TEFile.h"

TE::Resources::Resource::Resource(const std::string& filePath )
	:
	m_filePath(filePath),
    m_referenceCount(0)
{	
	m_fileExtention = IO::FileExtentionFromPath(m_filePath);
}

TE::Resources::Resource::Resource()
{

}

const U8* TE::Resources::Resource::GetDataFront() const
{
    return &(m_data.front());
}

void TE::Resources::Resource::SetData( DataIterator first, DataIterator last )
{
	m_data.assign(first, last);
    m_data.push_back('\0');
}

void TE::Resources::Resource::Unload()
{
	m_data.clear();
}

bool TE::Resources::Resource::IsLoaded() const
{
	return !m_data.empty();
}

I32 TE::Resources::Resource::GetDataSize() const
{
	//Data is null terminated so -1
	return m_data.size() - 1;
}

const std::string& TE::Resources::Resource::GetFileExtention() const
{
	return m_fileExtention;
}

void TE::Resources::Resource::Load( IO::FileIO& fileIO )
{
	assert(m_filePath != "" && "FilePath not set!");

	if (!IsLoaded())
	{
        fileIO.LoadFile(m_filePath, m_data);
        m_data.push_back('\0');
	}
}

const std::string& TE::Resources::Resource::GetFilePath() const
{
	return m_filePath;
}

void TE::Resources::Resource::SetFilePath( const std::string& filePath )
{
    m_filePath = filePath;
}

void TE::Resources::Resource::Save( IO::FileIO& fileIO )
{
	fileIO.SaveFile(m_filePath, m_data);
}

