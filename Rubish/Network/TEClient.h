#ifndef TECLIENT_H
#define TECLIENT_H

#include <unordered_map>
#include <TEHost.h>

namespace TE
{
	namespace Network
	{
		class Client
		{
		public:
			Client()
			{

			}

		private:
			std::unordered_map<unsigned, Host> m_connections;
		};
	}
}

#endif