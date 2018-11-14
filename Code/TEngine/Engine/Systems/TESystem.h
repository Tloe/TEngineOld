#ifndef TESYSTEM_H
#define TESYSTEM_H

#include "TEDataTypes.h"
#include "TEValue.h"

#include <vector>
#include <memory>
#include <string>

namespace TE
{
    namespace Engine { class EngineRoot; }
	namespace Engine { class SystemScene; typedef std::unique_ptr<SystemScene> SystemSceneUPtr; }

	namespace Engine
	{
		class System
		{
		public:
			virtual ~System();

            virtual U32 GetSystemId() = 0;
            virtual const std::string & GetSystemName() = 0;
            virtual void SetValue(Core::Value & value) = 0;
            virtual void Startup() = 0;
            virtual void Shutdown() = 0;
			virtual SystemSceneUPtr CreateScene() = 0;
		};

        typedef std::unique_ptr<System> SystemUPtr;
        typedef std::vector<SystemUPtr> SystemUPtrVec;

        class SystemFactory
        {
        public:
            virtual Enum ValueFromString(const std::string & valueStr) = 0;
            virtual const std::string & GetSystemName() = 0;
            virtual SystemUPtr Generate(U32 systemId, EngineRoot & engine, std::vector<Core::Value> & values) = 0;
        };
	}
}

#endif
