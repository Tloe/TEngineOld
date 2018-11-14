#include <TEServiceManager.h>
#include <assert.h>
#include <TEService.h>
#include "TEPlatformService.h"

TE::Engine::ServiceManager::ServiceMap TE::Engine::ServiceManager::s_services;
std::hash<std::string> TE::Engine::ServiceManager::s_hasher;

void TE::Engine::ServiceManager::RegisterService( Service& service )
{
	s_services.insert(std::make_pair(service.GetHash(), &service));
}

void TE::Engine::ServiceManager::DeregisterService( Service& service )
{
	s_services.erase(service.GetHash());
}

TE::Engine::Service& TE::Engine::ServiceManager::GetService( Hash serviceHash )
{
	assert(s_services.find(serviceHash) != s_services.end());

	return *s_services[serviceHash];
}

Hash TE::Engine::ServiceManager::GetStringHash( const std::string& hashString )
{
	return s_hasher(hashString);
}

TE::Engine::PlatformService* TE::Engine::ServiceManager::GetPlatformService()
{
	static const Hash platformServiceHash = s_hasher("PlatformService");
	assert(s_services.find(platformServiceHash) != s_services.end());
	
	return static_cast<PlatformService*>(s_services[platformServiceHash]);
}

