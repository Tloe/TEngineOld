#include "TEChangeSyncer.h"
#include "TEChangeMasks.h"
#include "TEFutureJoiner.h"
#include "TESubject.h"
#include "TEThreadPool.h"

#include <algorithm>
#include <iostream>
#include <set>

thread_local U32 TE::Engine::ChangeSyncer::m_localQuedChangesIndex;

TE::Engine::ChangeSyncer::ChangeSyncer(Threading::ThreadPool &threadPool)
    : m_threadPool(threadPool),
      m_frameNumber(0) {
    m_localChanges.resize(threadPool.GetThreadCount() + 1);

    {
        auto futures = m_threadPool.SubmitToAllThreads(std::bind(&ChangeSyncer::InitThreadData, this));

        Threading::FutureJoiner<void> joiner(futures);
    }

    m_localQuedChangesIndex = m_localChanges.size() - 1;
}

void TE::Engine::ChangeSyncer::ClearSubscriptions() {
    std::lock_guard<std::mutex> lock(m_updateMutex);
    for (U32 i = 0; i < m_threadPool.GetThreadCount(); ++i) {
        m_localChanges[i].clear();
    }

    m_subscriptions.clear();
}

void TE::Engine::ChangeSyncer::SyncronizeChanges() {
    ++m_frameNumber;

    GenerateTotalQuedChanges();

    U32 queuedChangesCount = m_changes.size();

    if (queuedChangesCount > 20) {
        U32 threadCount   = m_threadPool.GetThreadCount();

        U32 subRangeCount = (queuedChangesCount / threadCount) + 1;

        U32 subRangeBegin = 0;
        U32 subRangeEnd   = subRangeCount - 1;

        std::vector<std::future<bool>> futures;
        for (U32 i = 0; i < threadCount; ++i) {
            if (i == threadCount - 1) {
                subRangeEnd = queuedChangesCount - 1;
            }

            futures.push_back(m_threadPool.Submit(std::bind(&ChangeSyncer::RangedChangeDistribution,
                                                            this,
                                                            subRangeBegin,
                                                            subRangeEnd)));

            subRangeBegin = subRangeEnd + 1;
            subRangeEnd += subRangeCount;
        }

        Threading::FutureJoiner<bool> joiner(futures);
    } else if (queuedChangesCount != 0) {
        RangedChangeDistribution(0, m_changes.size());
    }
}

void TE::Engine::ChangeSyncer::RegisterChangeSubscription(Subject *subject, Bitmask64 changeBitsSubject, Observer *observer, Bitmask64 changeBitsObserver) {
    std::lock_guard<std::mutex> lock(m_updateMutex);
    subject->AttachObserver(*this, changeBitsSubject);

    auto findItr = m_subscriptions.find(subject);
    if (findItr == m_subscriptions.end()) {
        SubjectSubscriptions temp = {changeBitsObserver};
        temp.observers.push_back(observer);
        m_subscriptions.insert(std::make_pair(subject, std::move(temp)));
    } else {
        findItr->second.changeBits |= changeBitsObserver;
        findItr->second.observers.push_back(observer);
    }

    if (subject->GetObjectId() != -1) {
        const auto &begin   = std::begin(m_objectIdSubjects[subject->GetObjectId()]);
        const auto &end     = std::end(m_objectIdSubjects[subject->GetObjectId()]);

        const auto &findItr = std::find_if(begin, end, [&subject](SubjectInfo &subjectInfo) {
            return subject == subjectInfo.subject;
        });

        if (findItr == end) {
            SubjectInfo subjectInfo{subject, m_frameNumber, 0};
            m_objectIdSubjects[subject->GetObjectId()].push_back(std::move(subjectInfo));
        }
    }
}

void TE::Engine::ChangeSyncer::OnSubjectChange(Subject *subject, Bitmask64 changeBits) {
    m_localChanges[m_localQuedChangesIndex][subject] |= changeBits;
}

void TE::Engine::ChangeSyncer::InitThreadData() {
    m_localQuedChangesIndex = m_threadPool.GetLocalThreadIndex();
}

void TE::Engine::ChangeSyncer::GenerateTotalQuedChanges() {
    m_changes.clear();

    for (SubjectChangeMap &localQuedChanges : m_localChanges) {
        for (auto &mapItr : localQuedChanges) {
            SubjectInfo *subjectInfo                 = nullptr;
            SubjectInfo *updatedLowerPriSubjectInfo  = nullptr;
            SubjectInfo *updatedHigherPriSubjectInfo = nullptr;
            GetSubjectInfoPtrsFromSubject(mapItr.first, subjectInfo, updatedLowerPriSubjectInfo, updatedHigherPriSubjectInfo);

            assert(subjectInfo->updateFrame != m_frameNumber);

            Bitmask64 changeBits;
            if (updatedHigherPriSubjectInfo) {
                // Only the new changes not already stored for the subject with higher priority
                changeBits = (m_changes[updatedHigherPriSubjectInfo->changeIndex].changeBits ^ mapItr.second) & mapItr.second;
            } else {
                changeBits = mapItr.second;
            }

            if (changeBits) {
                subjectInfo->updateFrame = m_frameNumber;
                subjectInfo->changeIndex = m_changes.size();
                SubjectChange subjectChange{subjectInfo->subject, changeBits};
                m_changes.push_back(subjectChange);

                if (updatedLowerPriSubjectInfo) {
                    std::cout << "This needs some more logic; dont delete changes that is not updated (TEChangeSyncer.cpp bottom of GenerateTotalQuedChanges())" << std::endl;
                    m_changes[updatedLowerPriSubjectInfo->changeIndex].changeBits = Change::NotSet;
                }
            }
        }

        localQuedChanges.clear();
    }
}

bool TE::Engine::ChangeSyncer::RangedChangeDistribution(U32 rangeBegin, U32 rangeEnd) {
    for (U32 i = rangeBegin; i < rangeEnd; ++i) {
        SubjectChange &quedChange = m_changes[i];

        ObserverVec &observers    = m_subscriptions[quedChange.subject].observers;
        for (U32 j = 0; j < observers.size(); ++j) {
            if (quedChange.changeBits != Change::NotSet)
                observers[j]->OnSubjectChange(quedChange.subject, quedChange.changeBits);
        }
    }

    return true;
}

void TE::Engine::ChangeSyncer::GetSubjectInfoPtrsFromSubject(const Subject *subject, SubjectInfo *&subjectInfo, SubjectInfo *&lowerPriSubjectInfo, SubjectInfo *&higherPriSubjectInfo) {
    SubjectInfoVec &subjectInfos = m_objectIdSubjects.find(subject->GetObjectId())->second;

    for (SubjectInfo &subjInfo : subjectInfos) {
        if (subject == subjInfo.subject) {
            subjectInfo = &subjInfo;
        } else if (subjInfo.updateFrame == m_frameNumber &&
                   subject->GetPriority() > subjInfo.subject->GetPriority()) {
            lowerPriSubjectInfo = &subjInfo;
        } else if (subjInfo.updateFrame == m_frameNumber &&
                   subject->GetPriority() < subjInfo.subject->GetPriority()) {
            higherPriSubjectInfo = &subjInfo;
        }
    }

    assert(subjectInfo);
}
