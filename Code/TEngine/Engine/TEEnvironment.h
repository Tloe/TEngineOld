#ifndef TEENVIRONMENT_H
#define TEENVIRONMENT_H

#include "TEDataTypes.h"
#include "TEVariant.h"
#include "TEEventHandler.h"

#include <vector>

namespace TE
{
    namespace Event { class EventManager; }

	namespace Engine
	{
		enum class RuntimeState
		{
			Init,
			Update,
			Pause,
			Quit
		};

		enum class FrameRate
		{
            Hz30,
            Hz60
		};

        class Environment : public Event::EventHandler
		{
        public:
            Environment(Event::EventManager& eventManager);

            RuntimeState GetRuntimeState();

            virtual void HandleEvent(Event::EnvironmentUpdateEvent & environmentEvent);

            void SetRuntimeState(RuntimeState runtimeState);
            const Core::Variant & GetValue(std::string & name) const;

        private:
			RuntimeState m_runtimeState;
            struct NamedVariant
            {
                std::string name;
                Core::Variant value;
            };

            std::vector<NamedVariant> m_namedVariants;
		};
	}
}

#endif
