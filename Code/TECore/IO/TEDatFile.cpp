#include <TEDatFile.h>
#include <TECrypto.h>
#include <sstream>
#include <algorithm>
#include <TEDatPath.h>
#include <TEFileIO.h>
#include <iostream>
//#include <xfunctional>
#include <assert.h>
#include "TEFile.h"

TE::IO::DatFile::DatFile()
	:
	m_emptyFile(false)
{}

TE::IO::DatFile::DatFile( Resources::CryptoUPtr& crypto )
	:
	m_crypto(std::move(crypto)),
	m_emptyFile(false)
{}

bool TE::IO::DatFile::OpenFile( const std::string& filePath)
{
	m_filePath = filePath;
	if (m_datFile.IsOpen())
	{
		m_fileIndexHash.clear();
		m_fileIndexString.clear();
		m_emptyFile = false;
	}

	m_datFile.Open(m_filePath, std::ios::binary | std::ios::in | std::ios::out);

	if(m_datFile.IsOpen())
	{
		m_indexOffset = ReadDatIndexHash(m_datFile, m_fileIndexHash);
		if (m_indexOffset == -1)
		{
			std::clog << "Corrupt file";
			return false;
		}
	}
	else
	{
		//File does not exist, create it
	    m_datFile.Open(m_filePath, std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc); 
		if(!m_datFile.IsOpen())
		{
			std::clog << "Could not open file";
			return false;
		}
		m_emptyFile = true;
		m_indexOffset = 0;
	}

	return true;
}

bool TE::IO::DatFile::AddFile( const std::string& filePath, const DatPath& datPath)
{
	std::vector<U8> fileData;
	File inFile(filePath, std::ios::binary | std::ios::in);
	inFile.ReadData(fileData,0);

	return AddFile(fileData, datPath);
}

bool TE::IO::DatFile::AddFile( std::vector<U8>& data, const DatPath& datPath )
{
	if (m_fileIndexString.find(datPath.GetFullPath()) != m_fileIndexString.end()) return false;

	if(m_fileIndexString.empty() && !m_emptyFile) ActivateIndexStringMap();

	m_datFile.WriteData(data, m_indexOffset);
	SizeOffsetPair sizeOffset(data.size(), m_indexOffset);
	m_fileIndexString.insert(std::make_pair(datPath.GetFullPath(), sizeOffset));
	m_indexOffset += data.size();

	StringHash hash = HashGenerator()(datPath.GetFullPath());
	m_fileIndexHash.insert(std::make_pair(hash, sizeOffset));

	WriteDatIndex(m_datFile, m_fileIndexString, m_indexOffset);

	return true;
}

bool TE::IO::DatFile::NewFolder( const DatPath& datPath )
{
	assert(m_datFile.IsOpen() && "Dat file is not open.");
	if (m_fileIndexString.find(datPath.GetFullPath()) != m_fileIndexString.end()) return false;

	if(m_fileIndexString.empty() && !m_emptyFile) ActivateIndexStringMap();

	SizeOffsetPair sizeOffset(0, 0);

	m_fileIndexString.insert(std::make_pair(datPath.GetFullPath(), sizeOffset));
	WriteDatIndex(m_datFile, m_fileIndexString, m_indexOffset);

	StringHash hash = HashGenerator()(datPath.GetFullPath());
	m_fileIndexHash.insert(std::make_pair(hash, sizeOffset));

	return true;
}

void TE::IO::DatFile::RemovePath( const DatPath& datPath )
{
	//Delete index
	m_datFile.RemoveFileData(m_filePath, m_indexOffset);

	if (datPath.IsFolder()) //Folder
	{
		RemoveFolder(datPath);
	}
	else //File
	{
		RemoveFile(datPath);
	}

	//Update index offset and write index to file
	if (m_fileIndexString.empty())
	{
		m_emptyFile = true;
		m_indexOffset = 0;
	}
	else
	{
		UpdateIndexOffsets();
		WriteDatIndex(m_datFile, m_fileIndexString, m_indexOffset);
	}
}


void TE::IO::DatFile::RemoveFolder( const DatPath& datPath )
{
	std::vector<DatPath> filesToRemove;
	std::vector<DatPath> foldersToRemove;

	for(DatFileIndexStringMap::iterator itr = m_fileIndexString.begin();
		itr != m_fileIndexString.end(); ++itr)
	{
		DatPath currPath(itr->first);
		if (currPath.InSubPathOf(datPath) || currPath == datPath)
		{
			if (currPath.IsFile())
			{
				filesToRemove.push_back(currPath);
			}
			else
			{
				foldersToRemove.push_back(currPath);
			}
		}
	}

	for (unsigned i = 0; i < filesToRemove.size(); ++i)
	{
		RemoveFile(filesToRemove[i]);
	}

	for (unsigned i = 0; i < foldersToRemove.size(); ++i)
	{
		StringHash hash = HashGenerator()(foldersToRemove[i].GetFullPath());
		m_fileIndexHash.erase(hash);
		m_fileIndexString.erase(foldersToRemove[i].GetFullPath());
	}
}

void TE::IO::DatFile::RemoveFile( const DatPath& datPath )
{
	assert(m_datFile.IsOpen() && "Dat file is not open.");

	//delete data in file
	SizeOffsetPair& sizeOffset = m_fileIndexString[datPath.GetFullPath()];
	m_datFile.RemoveFileData(m_filePath, sizeOffset.second, sizeOffset.first);

	//Update indexes
	StringHash hash = HashGenerator()(datPath.GetFullPath());
	m_fileIndexHash.erase(m_fileIndexHash.find(hash));
	m_fileIndexString.erase(m_fileIndexString.find(datPath.GetFullPath()));
}


bool TE::IO::DatFile::GetFileData( StringHash filehash, std::vector<U8>& dataOut )
{
	assert(m_datFile.IsOpen() && "Dat file is not open.");
	
	if (m_fileIndexHash.find(filehash) != m_fileIndexHash.end())
	{
		const SizeOffsetPair& sizeoffset = m_fileIndexHash[filehash];
		
		dataOut.resize(sizeoffset.first);
		m_datFile.ReadData(dataOut, sizeoffset.second, sizeoffset.first);
		return true;
	}
	return false;
}

bool TE::IO::DatFile::GetFileData( const std::string& filePath, std::vector<U8>& dataOut )
{
	return GetFileData(HashGenerator()(filePath), dataOut);
}

TE::IO::DatFile::~DatFile()
{
	if (!m_datFile.IsOpen())
	{
		m_datFile.Open(m_filePath, std::ios::binary | std::ios::in | std::ios::out);
	}
	if (m_datFile.IsOpen())
	{
		if (m_datFile.GetFileSize() == 0 || m_fileIndexHash.empty())
		{
			remove(m_filePath.c_str());
		}
	}
}

I32 TE::IO::DatFile::GetFolderContent( const DatPath& relativeDatPath, std::vector<std::string>& foldersAndFilse )
{
	if(m_fileIndexString.empty() && !m_emptyFile) ActivateIndexStringMap();
	
	std::set<std::string> folderSet;
	std::set<std::string> fileSet;

	for(DatFileIndexStringMap::iterator itr = m_fileIndexString.begin();
		itr != m_fileIndexString.end(); ++itr)
	{
		DatPath newPath(itr->first);
		if (newPath.InSubPathOf(relativeDatPath))
		{
			if (newPath.IsFile())
			{
				fileSet.insert(newPath.GetFileOrFolder());
			}
			else
			{
				folderSet.insert(newPath.GetFolderIn(relativeDatPath));
			}
		}
	}

	foldersAndFilse.reserve(fileSet.size() + folderSet.size());
	foldersAndFilse.insert(foldersAndFilse.end(), folderSet.begin(), folderSet.end());
	foldersAndFilse.insert(foldersAndFilse.end(), fileSet.begin(), fileSet.end());

	return folderSet.size();
}

void TE::IO::DatFile::ActivateIndexStringMap()
{
	ReadDatIndexString(m_datFile, m_fileIndexString);
	m_emptyFile = false;
}

void TE::IO::DatFile::UpdateIndexOffsets()
{
	std::vector<std::pair<std::string, SizeOffsetPair> > stringIndexSorted;
	SortedIndex(stringIndexSorted, m_fileIndexString);

	std::vector<std::pair<StringHash, SizeOffsetPair> > hashIndexSorted;
	SortedIndex(hashIndexSorted, m_fileIndexHash);

	m_fileIndexString.clear();
	m_fileIndexHash.clear();
	I32 currentOffset = 0;
	for(unsigned i = 0; i < stringIndexSorted.size(); ++i)
	{
		if (!(stringIndexSorted[i].second.first == 0 && stringIndexSorted[i].second.first == stringIndexSorted[i].second.second))
		{
			//offset and file size is 0; path is file, update offset
			stringIndexSorted[i].second.second = currentOffset;
			hashIndexSorted[i].second.second = currentOffset;
			currentOffset += stringIndexSorted[i].second.first;
		}
		m_fileIndexString.insert(std::make_pair(stringIndexSorted[i].first,stringIndexSorted[i].second));
		m_fileIndexHash.insert(std::make_pair(hashIndexSorted[i].first, hashIndexSorted[i].second));
	}

	m_indexOffset = currentOffset;
}

I32 TE::IO::ReadDatIndexHash( File& file, DatFileIndexHashMap& fileIndex )
{
	if(file.GetFileSize() == 0) return 0;

	I32 indexOffset;
	I32 numlines;

	std::streamoff fileSize = file.GetFileSize();
	file.ReadData(reinterpret_cast<U8*>(&indexOffset), fileSize-(sizeof(I32)*2), sizeof(I32));
	file.ReadData(reinterpret_cast<U8*>(&numlines), fileSize-sizeof(I32), sizeof(I32));

	if (numlines <= 0 || numlines > 100000) return -1;

	size_t splitPos;
	std::string line;
	I32 currentOffset = 0;
	file.SetReadOffset(indexOffset);
	for (I32 i = 0; i < numlines; ++i)
	{
		file.ReadLine(line);
		splitPos = line.find_last_of(' ');

		StringHash hash = HashGenerator()(line.substr(0, splitPos));

		I32 fileSize = atoi(line.substr(splitPos+1).c_str());
		fileIndex.insert(std::make_pair(hash,
			std::make_pair(fileSize, currentOffset)));
		currentOffset += fileSize;
	}

	return indexOffset;
}

I32 TE::IO::ReadDatIndexString( File& file, DatFileIndexStringMap& fileIndex )
{
	if(file.GetFileSize() == 0) return 0;

	I32 indexOffset;
	I32 numlines;

	std::streamoff fileSize = file.GetFileSize();
	file.ReadData(reinterpret_cast<U8*>(&indexOffset), fileSize-(sizeof(I32)*2), sizeof(I32));
	file.ReadData(reinterpret_cast<U8*>(&numlines), fileSize-sizeof(I32), sizeof(I32));

	size_t splitPos;
	std::string line;
	I32 currentOffset = 0;
	file.SetReadOffset(indexOffset);
	for (I32 i = 0; i < numlines; ++i)
	{
		file.ReadLine(line);
		splitPos = line.find_last_of(' ');
		
		I32 fileSize = atoi(line.substr(splitPos+1).c_str());
		fileIndex.insert(std::make_pair(line.substr(0, splitPos),
			std::make_pair(fileSize, currentOffset)));
		currentOffset += fileSize;
	}

	return indexOffset;	
}

void TE::IO::WriteDatIndex( File& file, DatFileIndexStringMap& fileIndex, I32 offset )
{
	std::vector<std::pair<std::string, SizeOffsetPair> > stringIndexSorted;
	SortedIndex(stringIndexSorted, fileIndex);
	
	std::vector<std::pair<std::string, SizeOffsetPair> >::iterator currentItr = stringIndexSorted.begin(); 
	
	file.SetWriteOffset(offset);

	for(; currentItr != stringIndexSorted.end(); ++currentItr)
	{
		std::stringstream stringstr;
		stringstr << currentItr->first
			<< " " 
			<< currentItr->second.first
			<< "\n";

		std::string str(stringstr.str());
		std::vector<char> data(str.begin(), str.end());
		file.WriteData(reinterpret_cast<U8*>(&data[0]), data.size());
	}

	file.WriteData(reinterpret_cast<U8*>(&offset), static_cast<I32>(sizeof(I32)));
	I32 numLines = fileIndex.size();
	file.WriteData(reinterpret_cast<U8*>(&numLines), static_cast<I32>(sizeof(I32)));
}

