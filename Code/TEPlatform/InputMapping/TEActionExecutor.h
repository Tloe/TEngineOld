#ifndef TEACTIONEXECUTOR_H
#define TEACTIONEXECUTOR_H

#include "TEDataTypes.h"

#include <memory>
#include <string>

namespace TE
{
	namespace InputMapping
	{
		class ActionExecutor
		{
		public:
			friend class InputMapper;

			ActionExecutor(const std::string& actionName);
			virtual void Execute() = 0;

		private:
			Hash m_nameHash;
		};

		typedef std::unique_ptr<ActionExecutor> ActionExecutorUPtr;
	}
}

#endif