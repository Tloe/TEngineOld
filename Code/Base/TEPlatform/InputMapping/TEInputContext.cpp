#include "TEInputContext.h"
#include "TEAction.h"
#include "TEInput.h"
#include "TERange.h"
#include "TEState.h"

TE::InputMapping::InputContext::InputContext() {
}

/*void TE::InputMapping::InputContext::JSONDeserialize( const Json::Value& jsonValue )
{
        static HashGenerator hashGenerator;

        const Json::Value& jActions = jsonValue["Actions"];
        for (auto jAction = jActions.begin(); jAction != jActions.end(); ++jAction)
        {
                Action newAction;
                newAction.name = jAction.key().asString();
                newAction.nameHash = hashGenerator(jAction.key().asString());
                newAction.defaultKey = InputType::FromString((*jAction)["Default"].asString());
                newAction.userKey = InputType::FromString((*jAction)["User"].asString());

                m_actions.insert(std::make_pair(newAction.userKey, newAction));
        }

        const Json::Value& jStates = jsonValue["States"];
        for (auto jState = jStates.begin(); jState != jStates.end(); ++jState)
        {
                State newState;
                newState.name = jState.key().asString();
                newState.nameHash = hashGenerator(jState.key().asString());
                newState.defaultKey = InputType::FromString((*jState)["Default"].asString());
                newState.userKey = InputType::FromString((*jState)["User"].asString());

                m_states.insert(std::make_pair(newState.userKey, newState));
        }

        const Json::Value& jRanges = jsonValue["Ranges"];
        for (auto jRange = jRanges.begin(); jRange != jRanges.end(); ++jRange)
        {
                Range newRange;
                newRange.name = jRange.key().asString();
                newRange.nameHash = hashGenerator(jRange.key().asString());
                newRange.defaultRange = RangeInputFromString((*jRange)["Default"].asString());
                newRange.userRange = RangeInputFromString((*jRange)["User"].asString());
                newRange.defaultSensitivity = (*jRange)["DefaultSensitivity"].asInt();
                newRange.userSensitivity = (*jRange)["UserSensitivity"].asInt();
                newRange.minInput = (*jRange)["MinInput"].asDouble();
                newRange.maxInput = (*jRange)["MaxInput"].asDouble();
                newRange.minOutput = (*jRange)["MinOutput"].asDouble();
                newRange.maxOutput = (*jRange)["MaxOutput"].asDouble();

                m_ranges.insert(std::make_pair(newRange.userRange, newRange));
        }
}

void TE::InputMapping::InputContext::JSONSerialize( Json::Value& jsonValue )
{

}
*/

bool TE::InputMapping::InputContext::MapAction(InputType inputType, Action &action) {
    const auto &findItr = m_actions.find(inputType);

    if (findItr == m_actions.end())
        return false;

    action = findItr->second;

    return true;
}

bool TE::InputMapping::InputContext::MapState(InputType inputType, State &state) {
    const auto &findItr = m_states.find(inputType);

    if (findItr == m_states.end())
        return false;

    state = findItr->second;

    return true;
}

bool TE::InputMapping::InputContext::MapAxisToRange(RangeInput rangeInput, Range &range) {
    const auto &findItr = m_ranges.find(rangeInput);

    if (findItr == m_ranges.end())
        return false;

    range = findItr->second;

    return true;
}
