#ifndef TEINPUTCONTEXT_H
#define TEINPUTCONTEXT_H

#include "TEJson.h"
#include "TEActionExecutor.h"
#include "TEStateExecutor.h"
#include "TERangeExecutor.h"
#include "TEAction.h"
#include "TEState.h"
#include "TERange.h"
#include "TEInput.h"
#include "TEDataTypes.h"

#include <memory>
#include <unordered_map>
#include <map>

namespace TE
{
	namespace InputMapping
	{
		class InputContext// : public IO::JsonSerializer
		{
		public:
			InputContext();

			//virtual void JSONDeserialize( const Json::Value& jsonValue );
			//virtual void JSONSerialize( Json::Value& jsonValue );

			bool MapAction(InputType inputType, Action & action);
			bool MapState(InputType inputType, State & state);
			bool MapAxisToRange(RangeInput rangeInput, Range & range);
		private:
			typedef std::unordered_map<InputType, const Action> ActionMap;
			typedef std::unordered_map<InputType, const State> StateMap;
            typedef std::map<RangeInput, const Range> RangeMap;

			ActionMap m_actions;
			StateMap m_states;
			RangeMap m_ranges;
		};
	}
}

#endif
