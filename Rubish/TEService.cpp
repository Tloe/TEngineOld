#include <TEService.h>
#include "TEServiceManager.h"

TE::Engine::Service::Service( const std::string& serviceName )
	:
	m_serviceName(serviceName)
{
	
	m_serviceHash = ServiceManager::GetStringHash(m_serviceName);
}

Hash TE::Engine::Service::GetHash()
{
	return m_serviceHash;
}