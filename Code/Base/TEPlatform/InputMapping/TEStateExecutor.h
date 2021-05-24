#ifndef TESTATEEXECUTOR_H
#define TESTATEEXECUTOR_H

#include "TEDataTypes.h"
#include "TEState.h"

#include <memory>
#include <string>

namespace TE::InputMapping {
    class StateExecutor {
      public:
        virtual ~StateExecutor();
        friend class InputMapper;

        StateExecutor(const std::string &stateName);
        virtual void Execute(bool isOn) = 0;

      private:
        Hash m_nameHash;
    };

    using StateExecutorUPtr = std::unique_ptr<StateExecutor>;
}

#endif
