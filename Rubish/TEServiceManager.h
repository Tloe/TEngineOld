#ifndef TESERVICEMANAGER_H
#define TESERVICEMANAGER_H

#include <unordered_map>
#include "TEDataTypes.h"

namespace TE
{
	//Forward declaration
	namespace Engine { class Service; }
	namespace Engine { class PlatformService; }
	//End forward declaration

	namespace Engine
	{
		class ServiceManager
		{
		public:
			static void RegisterService(Service& service);
			static void DeregisterService(Service& service);
			static Service& GetService(Hash serviceHash);
			static Hash GetStringHash(const std::string& hashString);

			static PlatformService* GetPlatformService();
		private:
			typedef std::unordered_map<Hash, Service*> ServiceMap;

			static std::hash<std::string> s_hasher;
			static ServiceMap s_services;
			
		};
	}
}

#endif