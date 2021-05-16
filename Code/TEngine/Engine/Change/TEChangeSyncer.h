#ifndef TECHANGESYNCER_H
#define TECHANGESYNCER_H

#include "TEDataTypes.h"
#include "TEObserver.h"

#include <map>
#include <mutex>
#include <thread>
#include <vector>

namespace TE {
    namespace Threading {
        class ThreadPool;
    }
    namespace Engine {
        class Subject;
    }

    namespace Engine {
        class ChangeSyncer : public Observer {
          public:
            ChangeSyncer(Threading::ThreadPool &threadPool);

            void ClearSubscriptions();
            void RegisterChangeSubscription(Subject *subject, Bitmask64 subscribeBitsSubject, Observer *observer, Bitmask64 subscribeBitsObserver);
            void SyncronizeChanges();
            void OnSubjectChange(Subject *subject, Bitmask64 changeBits);
            void InitThreadData();

          private:
            typedef std::vector<Observer *> ObserverVec;
            struct SubjectSubscriptions {
                Bitmask64 changeBits;
                ObserverVec observers;
            };
            struct SubjectChange {
                Subject *subject;
                Bitmask64 changeBits;
            };
            typedef std::vector<SubjectChange> SubjectChangeVec;
            typedef std::map<Subject *, Bitmask> SubjectChangeMap;
            typedef std::vector<SubjectChangeMap> ThreadSubjectChangeMapVec;
            typedef std::map<Subject *, SubjectSubscriptions> SubjectSubscriptionsMap;
            struct SubjectInfo {
                Subject *subject;
                U32 updateFrame;
                U32 changeIndex;
            };
            typedef std::vector<SubjectInfo> SubjectInfoVec;
            typedef std::map<I32, SubjectInfoVec> ObjectIdSubjectInfosMap;

            void GenerateTotalQuedChanges();
            bool RangedChangeDistribution(U32 rangeBegin, U32 rangeEnd); // Return bool until msvc bug is fixed
            void GetSubjectInfoPtrsFromSubject(const Subject *subject, SubjectInfo *&subjectInfo, SubjectInfo *&lowerPriSubjectInfo, SubjectInfo *&higherPriSubjectInfo);

            std::mutex m_updateMutex;
            Threading::ThreadPool &m_threadPool;
            SubjectSubscriptionsMap m_subscriptions;
            ThreadSubjectChangeMapVec m_localChanges;
            SubjectChangeVec m_changes;
            ObjectIdSubjectInfosMap m_objectIdSubjects;
            U32 m_frameNumber;

            static thread_local U32 m_localQuedChangesIndex;
        };
    }
}

#endif
