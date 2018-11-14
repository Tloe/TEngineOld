#ifndef TEINPUTTASK_H
#define TEINPUTTASK_H

#include "TEDataTypes.h"
#include "TESystemTask.h"

namespace TE
{
	namespace Input { class InputScene; }

	namespace Input
	{
		class InputTask : public Engine::SystemTask
		{
		public:
			InputTask(InputScene& inputScene);

			virtual Hash GetSystemHash();
			virtual const std::string& GetSystemString();
			virtual void SetDeltaValues( U64 t, U64 dt );
			virtual void TaskExecution( bool threaded );
			virtual Bitmask GetTaskFlags();

		private:
			InputScene& m_inputScene;
		};
	}
}

#endif