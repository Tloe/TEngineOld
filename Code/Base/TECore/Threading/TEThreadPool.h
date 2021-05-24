#ifndef TETHREADPOOL_H
#define TETHREADPOOL_H

#include "TEDataTypes.h"
#include "TEFunctionWrapper.h"
#include "TELockQue.h"
#include "TEThreadJoiner.h"
#include "TEWorkStealingQue.h"

#include <assert.h>
#include <atomic>
#include <future>
#include <memory>
#include <thread>
#include <vector>

namespace TE::Threading {
    class ThreadPool {
      public:
        ThreadPool(U32 threadCount = std::thread::hardware_concurrency() - 1);
        ~ThreadPool();

        template <typename FunctionType>
        std::future<typename std::result_of<FunctionType()>::type> Submit(FunctionType function) {
            typedef typename std::result_of<FunctionType()>::type ResultType;

            m_workStealingDisabled.store(false);

            std::packaged_task<ResultType()> task(function);
            std::future<ResultType> result(task.get_future());
            if (m_localWorkQuePtr) {
                m_localWorkQuePtr->Push(std::move(task));
            } else {
                m_globalWorkQues.Push(std::move(task));
            }
            return result;
        }

        template <typename FunctionType>
        std::vector<std::future<typename std::result_of<FunctionType()>::type>>
        SubmitToAllThreads(FunctionType function) {
            assert(AllLocalWorkQuesEmpty() &&
                   "This should only be called in main thread while other threads are not running");

            typedef typename std::result_of<FunctionType()>::type ResultType;

            m_workStealingDisabled.store(true);

            std::vector<std::future<typename std::result_of<FunctionType()>::type>> result;
            for (U32 i = 0; i < m_localWorkQues.size(); ++i) {
                FunctionType f = function;
                std::packaged_task<ResultType()> task(f);
                result.push_back(task.get_future());
                m_localWorkQues[i]->Push(std::move(task));
            }

            return result;
        }

        void RunPendingTask();
        U32 GetThreadCount() const;
        static U32 GetLocalThreadIndex();

      private:
        typedef std::unique_ptr<WorkStealingQue> LocalQueUPtr;

        void WorkerFunction(U32 localWorkQueIndex);
        bool PopTaskFromLocalWorkQue(FunctionWrapper &task);
        bool PopTaskFromGlobalWorkQue(FunctionWrapper &task);
        bool PopTaskFromOtherLocalWorkQue(FunctionWrapper &task);
        bool AllLocalWorkQuesEmpty();

        std::atomic<bool> m_workStealingDisabled;
        std::atomic<bool> m_done;
        LockQue<FunctionWrapper> m_globalWorkQues;
        std::vector<LocalQueUPtr> m_localWorkQues;
        std::vector<std::thread> m_threads;
        ThreadJoiner m_threadJoiner;

        static thread_local U32 m_localThreadIndex;
        static thread_local WorkStealingQue *m_localWorkQuePtr;
    };
}

#endif
