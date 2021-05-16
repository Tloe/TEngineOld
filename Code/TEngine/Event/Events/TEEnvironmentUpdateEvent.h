#ifndef TEENVIRONMENTCHANGEEVENT_H
#define TEENVIRONMENTCHANGEEVENT_H

#include "TEEventVisitor.h"
#include "TEVariant.h"

#include <string>

namespace TE {
    namespace Event {
        class EventHandler;
    }

    namespace Event {
        class EnvironmentUpdateEvent : public EventVisitor {
          public:
            EnvironmentUpdateEvent(const std::string &name, Core::Variant &value);
            EnvironmentUpdateEvent(const std::string &name, Core::Variant value);
            virtual void VisitEventHandler(EventHandler &eventHandler);
            std::string &GetName();
            Core::Variant &GetValue();

          private:
            std::string m_name;
            Core::Variant m_value;
        };
    }
}

#endif
