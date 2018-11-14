#ifndef TESERVER_H
#define TESERVER_H

#include <unordered_map>
#include <TEHost.h>

namespace TE
{
	namespace Network
	{
		class Server
		{
		public:
			Server()
			{

			}

			~Server()
			{

			}

			void setMaxConnections(unsigned max)
			{
				m_maxConnections = max;
			}

			void setServerIp(const std::string &ip)
			{
				m_serverIp = ip;
			}

			void setServerPort(unsigned port)
			{
				m_serverPort = port;
			}
		private:
			unsigned							m_maxConnections;
			std::string							m_serverIp;
			unsigned							m_serverPort;
			std::unordered_map<unsigned, Host>	m_connections;
		};
	}
}

#endif