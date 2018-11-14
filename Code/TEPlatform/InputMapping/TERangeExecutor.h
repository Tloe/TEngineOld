#ifndef TERANGEEXECUTOR_H
#define TERANGEEXECUTOR_H

#include "TEDataTypes.h"

#include <memory>
#include <string>


namespace TE
{
	namespace InputMapping
	{
		class RangeExecutor
		{
		public:
			friend class InputMapper;

			RangeExecutor(const std::string& rangeName);
			virtual void Execute(F64 range) = 0;

		private:
			Hash m_nameHash;
		};

		typedef std::unique_ptr<RangeExecutor> RangeExecutorUPtr;
	}
}

#endif
