#include <TEPlatformService.h>
#include <TEFileIO.h>

TE::Engine::PlatformService::PlatformService( IO::FileIO& fileIO )
	:
	Service("PlatformService"),
	m_fileIO(fileIO)
{

}

TE::IO::FileIO& TE::Engine::PlatformService::GetFileIO()
{
	return m_fileIO;
}
