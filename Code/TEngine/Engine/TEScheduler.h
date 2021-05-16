#ifndef TESCHEDULER_H
#define TESCHEDULER_H

#include "TESystemScene.h"
#include "TESystemTask.h"
#include "TETimer.h"
#include "TEUniversalScene.h"

namespace TE {
    namespace Threading {
        class ThreadPool;
    }

    namespace Engine {
        class Scheduler {
          public:
            Scheduler(Threading::ThreadPool &threadPool);
            ~Scheduler();

            void RunDrawPassTasks(F32 interpolation);
            void RunUpdatePassTasks(U64 t, U64 dt);
            void SetScene(UniversalScene &scene);
            void EnableThreading();
            void DisableThreading();

          private:
            void PopulateQuesWithDrawTasks(F32 interpolation);
            void PopulateQuesWithNormalTasks(U64 t, U64 dt);
            void AddToQueBasedOnFlags(Bitmask flag, SystemTask *systemTask);
            void RunTaskQues(bool threaded);

            typedef std::vector<SystemTask *> SystemTaskVec;

            Threading::ThreadPool &m_threadPool;
            bool m_threadingEnabled;
            SystemTaskVec m_anyThreadQue;
            SystemTaskVec m_mainThreadQue;
            UniversalScene *m_currentUniversalScene;
        };
    }
}

#endif
