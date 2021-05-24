#ifndef TEINPUTMAPPER_H
#define TEINPUTMAPPER_H

#include "TEDataTypes.h"
#include "TEInput.h"
#include "TEInputContext.h"
#include "TEJson.h"
#include "TERangeExecutor.h"

#include <list>
#include <set>
#include <unordered_map>

namespace TE::IO {
  class FileIO;
}

namespace TE::InputMapping {
  class ActionExecutor;
  using ActionExecutorUPtr = std::unique_ptr<ActionExecutor>;

  class StateExecutor;
  using StateExecutorUPtr = std::unique_ptr<StateExecutor>;

  class RangeExecutor;
  using RangeExecutorUPtr = std::unique_ptr<RangeExecutor>;

  class InputMapper // : public IO::JsonSerializer
  {
  public:
    InputMapper(IO::FileIO &fileIO);

    void LoadInputFile(const std::string &filePath);

    // virtual void JSONDeserialize( const Json::Value& jsonValue );
    // virtual void JSONSerialize( Json::Value& jsonValue );

    void MapInput(InputType inputType, bool pressed, bool previouslyPressed);
    void MapRangeInput(RangeInput rangeInput, F64 rawValue);

    void Dispatch();

    void PushContext(const std::string &contextName);
    void PopContext(const std::string &contextName);

    void AddActionExecutor(ActionExecutorUPtr &actionExecutor, I32 priority);
    void AddStateExecutor(StateExecutorUPtr &stateExecutor, I32 priority);
    void AddRangeExecutor(RangeExecutorUPtr &rangeExecutor, I32 priority);

  private:
    using ActionExecutorPriorityMap = std::multimap<I32, ActionExecutorUPtr>;
    using StateExecutorPriorityMap  = std::multimap<I32, StateExecutorUPtr>;
    using RangeExecutorPriorityMap  = std::multimap<I32, RangeExecutorUPtr>;
    using ActionExecutorMap         = std::unordered_map<Hash, ActionExecutorPriorityMap>;
    using StateExecutorMap          = std::unordered_map<Hash, StateExecutorPriorityMap>;
    using RangeExecutorMap          = std::unordered_map<Hash, RangeExecutorPriorityMap>;
    using InputContextMap           = std::unordered_map<std::string, InputContext>;
    using InputcontextPtrList       = std::list<InputContext *>;

    bool MapAction(InputType inputType);
    void MapState(InputType inputType, bool pressed);

    IO::FileIO &m_fileIO;
    ActionExecutorMap m_actionExecutors;
    StateExecutorMap m_stateExecutors;
    RangeExecutorMap m_rangeExecutors;
    InputContextMap m_inputContexts;
    InputcontextPtrList m_activeInputContexts;
    std::set<Hash> m_mappedActions;
    std::map<Hash, bool> m_mappedStates;
    std::map<Hash, F64> m_mappedRanges;
  };
}

#endif
