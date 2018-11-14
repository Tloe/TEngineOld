#ifndef TEGAMESYSTEM_H
#define TEGAMESYSTEM_H

#include "TEDataTypes.h"
#include "TESystem.h"
#include "TEEngine.h"

#include <string>
#include <vector>

namespace TE
{
    namespace Game
    {
        class GameSystem : public Engine::System
        {
        public:
            GameSystem(U32 systemId, const std::string & systemName, Engine::EngineRoot &engine);

            virtual U32 GetSystemId();
            virtual const std::string & GetSystemName();
            virtual void SetValue(Core::Value & value);
            virtual void Startup();
            virtual void Shutdown();
            virtual Engine::SystemSceneUPtr CreateScene();

        private:
            U32 m_systemId;
            std::string m_systemName;
        };

        class GameSystemFactory : public Engine::SystemFactory
        {
            virtual Enum ValueFromString(const std::string & valueStr);
            virtual const std::string & GetSystemName();
            virtual Engine::SystemUPtr Generate(U32 systemId, Engine::EngineRoot & engine, std::vector<Core::Value> & values);
        };
    }
}

#endif
