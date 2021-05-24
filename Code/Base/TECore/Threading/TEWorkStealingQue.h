#ifndef TEWORKSTEALINGQUE_H
#define TEWORKSTEALINGQUE_H

#include "TEFunctionWrapper.h"
#include <deque>
#include <mutex>

namespace TE::Threading {
    class WorkStealingQue {
      public:
        WorkStealingQue();

        void Push(FunctionWrapper data);
        bool Empty() const;
        bool TryPop(FunctionWrapper &res);
        bool TrySteal(FunctionWrapper &res);

      private:
        WorkStealingQue(const WorkStealingQue &) {}
        WorkStealingQue &operator=(const WorkStealingQue &) { return *this; }

        std::deque<FunctionWrapper> m_que;
        mutable std::mutex m_queMutex;
    };
}

#endif
