#include "TEEnvironment.h"
#include "TEEnvironmentUpdateEvent.h"
#include "TEEventManager.h"

#include <algorithm>
#include <assert.h>

TE::Engine::Environment::Environment(TE::Event::EventManager &eventManager) {
    eventManager.Subscribe<Event::EnvironmentUpdateEvent>(this);
}

TE::Engine::RuntimeState TE::Engine::Environment::GetRuntimeState() { return m_runtimeState; }

void TE::Engine::Environment::HandleEvent(TE::Event::EnvironmentUpdateEvent &environmentEvent) {
    const auto &findItr = std::find_if(std::begin(m_namedVariants), std::end(m_namedVariants),
                                       [&environmentEvent](NamedVariant &valuePair) {
                                           return valuePair.name == environmentEvent.GetName();
                                       });

    if (findItr == std::end(m_namedVariants)) {
        NamedVariant valuePair{environmentEvent.GetName(), environmentEvent.GetValue()};
        m_namedVariants.emplace_back(std::move(valuePair));
    } else {
        findItr->value = environmentEvent.GetValue();
    }
}

void TE::Engine::Environment::SetRuntimeState(TE::Engine::RuntimeState runtimeState) {
    m_runtimeState = runtimeState;
}

const TE::Core::Variant &TE::Engine::Environment::GetValue(std::string &name) const {
    const auto &findItr =
        std::find_if(std::begin(m_namedVariants), std::end(m_namedVariants),
                     [&name](const NamedVariant &valuePair) { return valuePair.name == name; });

    assert(findItr != std::end(m_namedVariants));

    return findItr->value;
}
