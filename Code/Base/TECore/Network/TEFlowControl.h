#ifndef TEFLOWCONTROLL_H
#define TEFLOWCONTROLL_H

#include "TEDataTypes.h"

namespace TE::Net {
    class FlowControl {
      public:
        FlowControl();

        void Reset();
        void Update(U64 deltaTime, U64 rtt);
        U32 GetSendRate();

      private:
        enum class Mode { Good, Bad };

        Mode mode;
        U64 m_penaltyTime;
        U64 m_goodConditionsTime;
        U64 m_penaltyReductionAccumulator;
    };
}

#endif
