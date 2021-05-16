#include "TEScheduler.h"
#include "TEEnvironment.h"
#include "TEFutureJoiner.h"
#include "TESystemTask.h"
#include "TEThreadPool.h"

#include <assert.h>
#include <chrono>
#include <functional>

TE::Engine::Scheduler::Scheduler(Threading::ThreadPool &threadPool)
    : m_threadPool(threadPool),
      m_threadingEnabled(true),
      m_currentUniversalScene(nullptr) {
}

TE::Engine::Scheduler::~Scheduler() {
}

void TE::Engine::Scheduler::RunDrawPassTasks(F32 interpolation) {
    if (m_currentUniversalScene) {
        PopulateQuesWithDrawTasks(interpolation);
        RunTaskQues(m_threadingEnabled);
    }
}

void TE::Engine::Scheduler::RunUpdatePassTasks(U64 t, U64 dt) {
    if (m_currentUniversalScene) {
        PopulateQuesWithNormalTasks(t, dt);
        RunTaskQues(m_threadingEnabled);
    }
}

void TE::Engine::Scheduler::SetScene(UniversalScene &scene) {
    m_currentUniversalScene = &scene;
}

void TE::Engine::Scheduler::EnableThreading() {
    m_threadingEnabled = true;
}

void TE::Engine::Scheduler::DisableThreading() {
    m_threadingEnabled = false;
}

void TE::Engine::Scheduler::PopulateQuesWithDrawTasks(F32 interpolation) {
    auto &systemScenes = m_currentUniversalScene->GetSystemScenes();

    for (auto &itr : systemScenes) {
        auto systemTask = itr.second->GetSystemTask();
        if (systemTask) {
            Bitmask taskFlags = systemTask->GetTaskFlags();
            if (taskFlags & TaskFlags::DrawingTask) {
                if (taskFlags & TaskFlags::RunInMainThread)
                    m_mainThreadQue.push_back(systemTask);
                else
                    m_anyThreadQue.push_back(systemTask);
                systemTask->SetInterpolation(interpolation);
            }
        }
    }
}

void TE::Engine::Scheduler::PopulateQuesWithNormalTasks(U64 t, U64 dt) {
    auto &systemScenes = m_currentUniversalScene->GetSystemScenes();

    for (auto &itr : systemScenes) {
        auto systemTask = itr.second->GetSystemTask();
        if (systemTask) {
            Bitmask taskFlags = systemTask->GetTaskFlags();
            if (taskFlags ^ TaskFlags::DrawingTask) {
                if (taskFlags & TaskFlags::RunInMainThread)
                    m_mainThreadQue.push_back(systemTask);
                else
                    m_anyThreadQue.push_back(systemTask);
                systemTask->SetDeltaValues(t, dt);
            }
        }
    }
}

void TE::Engine::Scheduler::RunTaskQues(bool threaded) {
    if (threaded) {
        std::vector<std::future<void>> futures;

        for (auto &task : m_anyThreadQue) {
            futures.push_back(m_threadPool.Submit(std::bind(&Engine::SystemTask::Run, task)));
        }
        m_anyThreadQue.clear();

        for (auto &task : m_mainThreadQue) {
            task->Run();
        }
        m_mainThreadQue.clear();
        Threading::FutureJoiner<void> joiner(futures);
    } else {
        for (auto &task : m_anyThreadQue) {
            task->Run();
        }
        m_anyThreadQue.clear();

        for (auto &task : m_mainThreadQue) {
            task->Run();
        }
        m_mainThreadQue.clear();
    }
}
