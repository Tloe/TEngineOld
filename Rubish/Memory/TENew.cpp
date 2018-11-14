#include <TENew.h>
#include <map>
#include <sstream>
#include <xutility>
#include <vector>
#include <fstream>

std::string TE::Memory::NewReplacement::GetMemoryLogString()
{
	std::stringstream strStream;
	std::map<unsigned, NewInfo> sortedInfo;

	unsigned maxFileName = 0;
	unsigned maxId = 0;

	for(NewInfoMap::iterator itr = GetNewInfoMap().begin();
		itr != GetNewInfoMap().end(); ++itr)
	{
		maxFileName = std::max(maxFileName, itr->second.filename.size());
		maxId = std::max(maxId, itr->second.id);
		sortedInfo.insert(std::make_pair(itr->second.id, itr->second));
	}

	for(std::map<unsigned, NewInfo>::iterator itr = sortedInfo.begin();
		itr != sortedInfo.end(); ++itr)
	{
		strStream << itr->second.id << "\t" <<   itr->second.filename << 
			std::string(maxFileName - itr->second.filename.size() + 3, ' ') <<
			"Line " << itr->second.line << "\t\tBytes " << itr->second.bytes << "\r\n";
	}

	return strStream.str();
}

void TE::Memory::NewReplacement::PrintMemoryLogToClog()
{
	std::clog << GetMemoryLogString();
}

void TE::Memory::NewReplacement::PrintMemoryLog()
{
	std::cout << GetMemoryLogString();
}

void TE::Memory::NewReplacement::PrintMemoryLogToFile( const std::string& filename )
{
	// Have to use std::fstream as the TEngine file uses the new replacement, causing cyclic dependencies.
	std::fstream file(filename, std::ios::out | std::ios::binary);

	std::string logString = GetMemoryLogString();
	std::vector<U8> data(logString.begin(), logString.end());
	file.write(reinterpret_cast<char*>(&data[0]), data.size());
	file.close();
}

void* TE::Memory::NewReplacement::Allocate( size_t bytes, U32 dimensions ) const
{
	void* memory;
	if (m_allocator == -1)
	{
		memory = malloc(bytes);
	}
	else
	{
		//memory = s_allocators.GetAllocator(m_allocator)->Allocate(bytes);
	}

	static unsigned id = 0;
	NewInfo newInfo = { id++, m_filename, m_line, bytes, dimensions };
	GetNewInfoMap().insert(std::make_pair(memory, newInfo));

	return memory;
}

void TE::Memory::NewReplacement::Deallocate( void* memory )
{
	if (m_allocator == -1)
	{
		free(memory);
	}
	else
	{
		//s_allocators.GetAllocator(m_allocator)->Deallocate(memory);
	}

	GetNewInfoMap().erase(memory);
}

TE::Memory::NewReplacement::NewInfoMap& TE::Memory::NewReplacement::GetNewInfoMap()
{
	//Static memory so its ok to "leak" as OS will take care of it when it exits
	static NewInfoMap* s_memoryMap = new NewInfoMap;
	return *s_memoryMap;
}


