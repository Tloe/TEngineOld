#ifndef TESERVICE_H
#define TESERVICE_H

#include <string>
#include "TEDataTypes.h"

namespace TE
{
	namespace Engine
	{
		class Service
		{
		public:
			Hash GetHash();
		protected:
			Service(const std::string& serviceName);
		private:
			std::string m_serviceName;
			Hash m_serviceHash;
		};
	}
}

#endif