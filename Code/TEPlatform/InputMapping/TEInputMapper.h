#ifndef TEINPUTMAPPER_H
#define TEINPUTMAPPER_H

#include "TEJson.h"
#include "TEInputContext.h"
#include "TEDataTypes.h"
#include "TEInput.h"

#include <unordered_map>
#include <set>
#include <list>

namespace TE
{
	namespace IO { class FileIO; }
	namespace InputMapping { class ActionExecutor; typedef std::unique_ptr<ActionExecutor> ActionExecutorUPtr; }
	namespace InputMapping { class StateExecutor; typedef std::unique_ptr<StateExecutor> StateExecutorUPtr; }
	namespace InputMapping { class RangeExecutor; typedef std::unique_ptr<RangeExecutor> RangeExecutorUPtr; }

	namespace InputMapping
	{
		class InputMapper// : public IO::JsonSerializer
		{
		public:
            InputMapper(IO::FileIO & fileIO);

            void LoadInputFile(const std::string& filePath);

			//virtual void JSONDeserialize( const Json::Value& jsonValue );
			//virtual void JSONSerialize( Json::Value& jsonValue );
			
			void MapInput(Enum inputType, bool pressed, bool previouslyPressed);
			void MapRangeInput(RangeInput rangeInput, F64 rawValue);

			void Dispatch();

			void PushContext(const std::string & contextName);
			void PopContext(const std::string & contextName);
			
            void AddActionExecutor(ActionExecutorUPtr & actionExecutor, I32 priority);
            void AddStateExecutor(StateExecutorUPtr & stateExecutor, I32 priority);
            void AddRangeExecutor(RangeExecutorUPtr & rangeExecutor, I32 priority);
			
		private:
            typedef std::multimap<I32, ActionExecutorUPtr> ActionExecutorPriorityMap;
            typedef std::multimap<I32, StateExecutorUPtr> StateExecutorPriorityMap;
            typedef std::multimap<I32, RangeExecutorUPtr> RangeExecutorPriorityMap;
			typedef std::unordered_map<Hash, ActionExecutorPriorityMap> ActionExecutorMap;
			typedef std::unordered_map<Hash, StateExecutorPriorityMap> StateExecutorMap;
			typedef std::unordered_map<Hash, RangeExecutorPriorityMap> RangeExecutorMap;
			typedef std::unordered_map<std::string, InputContext> InputContextMap;
			typedef std::list<InputContext*> InputcontextPtrList;

			bool MapAction(Hash inputType);
			void MapState(Hash inputType, bool pressed);

            IO::FileIO & m_fileIO;
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
}

#endif
