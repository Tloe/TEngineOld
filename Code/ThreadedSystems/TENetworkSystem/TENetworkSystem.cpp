#include "TENetworkSystem.h"
#include "TENetworkScene.h"
#include "TEEnvironmentUpdateEvent.h"
#include "TEEventManager.h"
#include "TEEngine.h"
#include "TEValue.h"
#include "TENetworkManager.h"

TE::Network::NetworkSystem::NetworkSystem(U32 systemId, const std::string &systemName, Engine::EngineRoot & engine)
    : m_systemId(systemId)
    , m_systemName(systemName)
    , m_eventManager(engine.GetEventManager())
{
    m_eventManager.Subscribe<Event::EnvironmentUpdateEvent>(&m_networkManager);
}

TE::Network::NetworkSystem::~NetworkSystem()
{

}

void TE::Network::NetworkSystem::SetValue(TE::Core::Value &value)
{
    switch(value.GetValueType())
    {
        case Values::Mode:
        {
            bool serverMode = value.GetString() == "Server";
            m_networkManager.SetServerMode(serverMode);
        }
        break;
        case Values::Port:
        {
            m_networkManager.SetPort(value.GetString());
        }
        break;
        case Values::IpFamily:
        {
            if(value.GetString() == "IPv4")
                m_networkManager.SetIpFamily(Net::IPFamily::IPv4);
            else
                m_networkManager.SetIpFamily(Net::IPFamily::IPv6);
        }
        break;
        case Values::Connect:
        {
            std::string ip = value.GetString();
            std::string port = value.GetString();
            Net::IPFamily ipFamily = Net::IPFamily::IPv4;
            if(value.GetString() == "IPv6")
                ipFamily = Net::IPFamily::IPv6;
            Net::Address address(ip, port, ipFamily);
            m_networkManager.Connect(address);
        }
        break;
    }
}

void TE::Network::NetworkSystem::Startup()
{
    m_networkManager.Initialize();
}

void TE::Network::NetworkSystem::Shutdown()
{
    m_networkManager.Cleanup();
}

U32 TE::Network::NetworkSystem::GetSystemId()
{
    return m_systemId;
}

const std::string &TE::Network::NetworkSystem::GetSystemName()
{
    return m_systemName;
}

TE::Engine::SystemSceneUPtr TE::Network::NetworkSystem::CreateScene()
{
    return std::make_unique<NetworkScene>(m_eventManager, m_networkManager);
}

TE::Network::NetworkManager &TE::Network::NetworkSystem::GetNetworkManager()
{
    return m_networkManager;
}

Enum TE::Network::NetworkSystemFactory::ValueFromString(const std::string &valueStr)
{
    if(valueStr == "Mode")
        return NetworkSystem::Values::Mode;
    if(valueStr == "Port")
        return NetworkSystem::Values::Port;
    if(valueStr == "IpFamily")
        return NetworkSystem::Values::IpFamily;

    assert(false);
    return -1;
}

const std::string &TE::Network::NetworkSystemFactory::GetSystemName()
{
    static std::string name("Network");
    return name;
}

TE::Engine::SystemUPtr TE::Network::NetworkSystemFactory::Generate(U32 systemId, TE::Engine::EngineRoot &engine, std::vector<Core::Value> &values)
{
    auto networkSystem = std::make_unique<Network::NetworkSystem>(systemId, "Network", engine);

    for(U32 i = 0; i < values.size(); ++i)
    {
        networkSystem->SetValue(values[i]);
    }

    return std::move(networkSystem);
}
