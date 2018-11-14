#ifndef TEMEMORYDEBUG_H
#define TEMEMORYDEBUG_H

#ifdef _DEBUG
#include <list>
#include <string>
#include <sstream>

struct AllocationInfo
{
	DWORD		address;
	DWORD		size;
	std::string	filename;
	DWORD		line;
};

typedef std::list<AllocationInfo*> AllocList;
AllocList *allocList;

void AddTrack(DWORD addr,  DWORD asize,  const char *filename, DWORD lnum)
{
	AllocationInfo *info;

	if(!allocList) {
		allocList = new(AllocList);
	}

	info = new(AllocationInfo);
	info->address = addr;
	info->filename = filename;
	info->line = lnum;
	info->size = asize;
	allocList->insert(allocList->begin(), info);
};

void RemoveTrack(DWORD addr)
{
	AllocList::iterator i;

	if(!allocList) return;

	for(i = allocList->begin(); i != allocList->end(); i++)
	{
		if((*i)->address == addr)
		{
			allocList->remove((*i));
			break;
		}
	}
};

void DumpUnfreed()
{
	std::stringstream strStream;

	if(!allocList) return;

	DWORD totalSize = 0;
	for(AllocList::iterator itr = allocList->begin();
		itr != allocList->end(); ++itr)
	{
		strStream << (*itr)->filename << ":\t\tLine " << (*itr)->line <<
			"\t\tAddress " << (*itr)->address <<
			"\t\tSize" << (*itr)->size <<
			std::endl;
		totalSize += (*itr)->size;
	}
	
	strStream << "-----------------------------------------------------------" << std::endl;
	strStream << "Total unfreed in bytes: " << totalSize << std::endl;

	OutputDebugString(strStream.str().c_str());
};

inline void * __cdecl operator new(unsigned int size, const char *file, int line)
{
	void *ptr = (void *)malloc(size);
	AddTrack((DWORD)ptr, size, file, line);
	return(ptr);
};

inline void __cdecl operator delete(void *p, const char *file, int line)
{
	RemoveTrack((DWORD)p);
	free(p);
};

#define DEBUG_NEW new(__FILE__, __LINE__)
#define new DEBUG_NEW

#define DEBUG_DELETE delete(__FILE__, __LINE__)
#define delete DEBUG_DELETE

//#define DEBUG_NEW new[](__FILE__, __LINE__)
//#define new DEBUG_NEW

#endif

#endif