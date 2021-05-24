#include "TEThreadPool.h"

thread_local TE::Threading::WorkStealingQue *TE::Threading::ThreadPool::m_localWorkQuePtr;
thread_local U32 TE::Threading::ThreadPool::m_localThreadIndex;

TE::Threading::ThreadPool::ThreadPool(U32 threadCount)
    : m_workStealingDisabled(false),
      m_done(false),
      m_threadJoiner(m_threads) {
    try {
        for (U32 i = 0; i < threadCount; ++i) {
            m_localWorkQues.push_back(std::make_unique<WorkStealingQue>());
        }
        for (U32 i = 0; i < threadCount; ++i) {
            m_threads.push_back(std::thread(&ThreadPool::WorkerFunction, this, i));
        }
    } catch (...) {
        m_done = true;
        throw;
    }
}

TE::Threading::ThreadPool::~ThreadPool() { m_done = true; }

void TE::Threading::ThreadPool::RunPendingTask() {
    FunctionWrapper task;
    if (PopTaskFromLocalWorkQue(task) || PopTaskFromGlobalWorkQue(task) ||
        (!m_workStealingDisabled && PopTaskFromOtherLocalWorkQue(task))) {
        task();
    } else {
        std::this_thread::yield();
    }
}

U32 TE::Threading::ThreadPool::GetThreadCount() const { return m_threads.size(); }

void TE::Threading::ThreadPool::WorkerFunction(U32 localThreadIndex) {
    m_localThreadIndex = localThreadIndex;
    m_localWorkQuePtr  = m_localWorkQues[m_localThreadIndex].get();
    while (!m_done) {
        RunPendingTask();
    }
}

bool TE::Threading::ThreadPool::PopTaskFromLocalWorkQue(FunctionWrapper &task) {
    return m_localWorkQuePtr && m_localWorkQuePtr->TryPop(task);
}

bool TE::Threading::ThreadPool::PopTaskFromGlobalWorkQue(FunctionWrapper &task) {
    return m_globalWorkQues.TryPop(task);
}

bool TE::Threading::ThreadPool::PopTaskFromOtherLocalWorkQue(FunctionWrapper &task) {
    for (U32 i = 0; i < m_localWorkQues.size(); ++i) {
        U32 index = (m_localThreadIndex + i + 1) % m_localWorkQues.size();

        if (m_localWorkQues[index]->TrySteal(task)) {
            return true;
        }
    }

    return false;
}

bool TE::Threading::ThreadPool::AllLocalWorkQuesEmpty() {
    for (LocalQueUPtr &que : m_localWorkQues) {
        if (!que->Empty())
            return false;
    }

    return true;
}

U32 TE::Threading::ThreadPool::GetLocalThreadIndex() { return m_localThreadIndex; }
