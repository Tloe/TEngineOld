#ifndef TECHANGESYNCER_H
#define TECHANGESYNCER_H

#include "TEDataTypes.h"
#include "TEObserver.h"

#include <map>
#include <mutex>
#include <thread>
#include <vector>

namespace TE::Threading {
  class ThreadPool;
}

namespace TE::Engine {
  class Subject;

  class ChangeSyncer : public Observer {
  public:
    ChangeSyncer(Threading::ThreadPool &threadPool);

    void ClearSubscriptions();
    void RegisterChangeSubscription(Subject *subject,
                                    Bitmask64 subscribeBitsSubject,
                                    Observer *observer,
                                    Bitmask64 subscribeBitsObserver);
    void SyncronizeChanges();
    void OnSubjectChange(Subject *subject, Bitmask64 changeBits);
    void InitThreadData();

  private:
    using ObserverVec = std::vector<Observer *>;

    struct SubjectSubscriptions {
      Bitmask64 changeBits;
      ObserverVec observers;
    };

    struct SubjectChange {
      Subject *subject;
      Bitmask64 changeBits;
    };

    using SubjectChangeVec          = std::vector<SubjectChange>;
    using SubjectChangeMap          = std::map<Subject *, Bitmask>;
    using ThreadSubjectChangeMapVec = std::vector<SubjectChangeMap>;
    using SubjectSubscriptionsMap   = std::map<Subject *, SubjectSubscriptions>;

    struct SubjectInfo {
      Subject *subject;
      U32 updateFrame;
      U32 changeIndex;
    };

    using SubjectInfoVec          = std::vector<SubjectInfo>;
    using ObjectIdSubjectInfosMap = std::map<I32, SubjectInfoVec>;

    void GenerateTotalQuedChanges();
    bool RangedChangeDistribution(U32 rangeBegin,
                                  U32 rangeEnd); // Return bool until msvc bug is fixed
    void GetSubjectInfoPtrsFromSubject(const Subject *subject,
                                       SubjectInfo *&subjectInfo,
                                       SubjectInfo *&lowerPriSubjectInfo,
                                       SubjectInfo *&higherPriSubjectInfo);

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

#endif
