#include "TEInputMapper.h"
#include "TEAction.h"
#include "TEFile.h"
#include "TEFileIO.h"
#include "TEInput.h"

TE::InputMapping::InputMapper::InputMapper(IO::FileIO &fileIO) : m_fileIO(fileIO) {}

void TE::InputMapping::InputMapper::LoadInputFile(const std::string &filePath) {
    std::vector<U8> data;
    m_fileIO.LoadFile(filePath, data);

    // Json::Value jsonData;
    // IO::JsonValueFromData(&(data.front()), &(data.back()), jsonData);
    // JSONDeserialize(jsonData);
}

/*void TE::InputMapping::InputMapper::JSONDeserialize( const Json::Value& jsonValue )
{
    for(std::string & contextName : jsonValue.getMemberNames())
        {
                InputContext inputContext;
                inputContext.JSONDeserialize(jsonValue[contextName]);
                m_inputContexts.insert(std::make_pair(contextName, std::move(inputContext)));
        }
}

void TE::InputMapping::InputMapper::JSONSerialize( Json::Value& jsonValue )
{

}
*/
void TE::InputMapping::InputMapper::MapInput(InputType inputType,
                                             bool pressed,
                                             bool previouslyPressed) {
    if (pressed && !previouslyPressed) {
        if (MapAction(inputType))
            return;
    }

    MapState(inputType, pressed);
}

void TE::InputMapping::InputMapper::MapRangeInput(RangeInput rangeInput, F64 rawValue) {
    Range range;
    for (auto &itr : m_inputContexts) {
        if (itr.second.MapAxisToRange(rangeInput, range)) {
            F64 normalizedValue = ConvertRange(range, rawValue);
            m_mappedRanges[range.nameHash] += normalizedValue;
        }
    }
}

bool TE::InputMapping::InputMapper::MapAction(InputType inputType) {
    Action action;
    for (auto &itr : m_inputContexts) {
        if (itr.second.MapAction(inputType, action)) {
            m_mappedActions.insert(action.nameHash);
            return true;
        }
    }

    return false;
}

void TE::InputMapping::InputMapper::MapState(InputType inputType, bool pressed) {
    State state;
    for (auto &itr : m_inputContexts) {
        if (itr.second.MapState(inputType, state)) {
            if (pressed) {
                bool isOn = true;
                m_mappedStates.insert(std::make_pair(state.nameHash, isOn));
            } else {
                if (m_mappedStates[state.nameHash] == false) {
                    // Was turned off last frame so delete mapped state
                    m_mappedStates.erase(state.nameHash);
                } else {
                    bool isOn = false;
                    m_mappedStates.insert(std::make_pair(state.nameHash, isOn));
                }
            }
        }
    }
}

void TE::InputMapping::InputMapper::Dispatch() {
    for (auto &actionItr : m_mappedActions) {
        for (auto &actionExecutorItr : m_actionExecutors[actionItr]) {
            actionExecutorItr.second->Execute();
        }
    }
    m_mappedActions.clear();

    for (auto &stateItr : m_mappedStates) {
        for (auto &stateExecutorItr : m_stateExecutors[stateItr.first]) {
            stateExecutorItr.second->Execute(stateItr.second);
        }
    }

    for (auto &rangeItr : m_mappedRanges) {
        for (auto &rangeExecutorItr : m_rangeExecutors[rangeItr.first]) {
            rangeExecutorItr.second->Execute(rangeItr.second);
        }
    }
    m_mappedRanges.clear();
}

void TE::InputMapping::InputMapper::PushContext(const std::string &contextName) {
    auto findItr = m_inputContexts.find(contextName);

    assert(findItr != m_inputContexts.end() && "Invalid context pushed");

    m_activeInputContexts.push_front(&findItr->second);
}

void TE::InputMapping::InputMapper::PopContext(const std::string &contextName) {
    if (!m_activeInputContexts.empty())
        m_activeInputContexts.pop_front();
}

void TE::InputMapping::InputMapper::AddActionExecutor(ActionExecutorUPtr &actionExecutor,
                                                      I32 priority) {
    Hash nameHash = actionExecutor->m_nameHash;
    m_actionExecutors[nameHash].insert(std::make_pair(priority, std::move(actionExecutor)));
}

void TE::InputMapping::InputMapper::AddStateExecutor(StateExecutorUPtr &stateExecutor,
                                                     I32 priority) {
    Hash nameHash = stateExecutor->m_nameHash;
    m_stateExecutors[nameHash].insert(std::make_pair(priority, std::move(stateExecutor)));
}

void TE::InputMapping::InputMapper::AddRangeExecutor(RangeExecutorUPtr &rangeExecutor,
                                                     I32 priority) {
    Hash nameHash = rangeExecutor->m_nameHash;
    m_rangeExecutors[nameHash].insert(std::make_pair(priority, std::move(rangeExecutor)));
}
