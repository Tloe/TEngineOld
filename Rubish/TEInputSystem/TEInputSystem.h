#ifndef TEINPUTSYSTEM_H
#define TEINPUTSYSTEM_H

#include "TEDataTypes.h"
#include "TESystem.h"

#include <unordered_map>

namespace TE
{
	namespace Platform { class PlatformWindow; }

	namespace Input
	{
		Hash GetSystemHash();
		const std::string& GetSystemString();

		struct InputMapping
		{
			std::string inputString;
			Bitmask inputStateFlags;
			Hash objectHash;
			Hash actionHash;
		};

		class InputSystem : public Engine::System
		{
		public:
			InputSystem(Platform::PlatformWindow& platformWindow);
			virtual ~InputSystem();

			virtual void Initialize();
			virtual void Cleanup();
			virtual Hash GetSystemHash();
			virtual const std::string& GetSystemString();
			virtual Engine::SystemSceneUPtr CreateScene();
			virtual void SetProperties( const Engine::PropertyVec& properties );
			virtual void GetProperties( Engine::PropertyVec& properties );
			
			void SetInputGroup(Enum inputGroup);
			bool GetMapping(Enum teInput, InputMapping& inputMapping);
			void SetMapping(Enum inputGroup,
							const std::string& inputString,			
							Enum teInput,			
							Bitmask inputStateFlags,
							Hash objectHash,
							Hash actionHash);

		private:
			typedef std::unordered_map<Enum, InputMapping> InputMappingMap;
			typedef std::unordered_map<Enum, InputMappingMap> InputStateMappingMap;

			Enum m_inputGroup;
			InputStateMappingMap m_inputMappings;
			Platform::PlatformWindow& m_platformWindow;
		};
	}
}

#endif