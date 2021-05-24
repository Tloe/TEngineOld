#ifndef TESUBJECT_H
#define TESUBJECT_H

#include "TEChangeData.h"
#include "TEDataTypes.h"

#include <memory>
#include <mutex>
#include <vector>

namespace TE::Engine {
  class Observer;

  class Subject {
  public:
    enum class Priority { Level0, Level1, Level2, Level3, Level4 };

    struct ObserverSubscription {
      Observer *observer;
      Bitmask64 subscribeBits;
    };

    typedef std::vector<ObserverSubscription> ObserverSubscriptionVec;

    void PostSubjectChanges(Bitmask64 changeBits);
    virtual Change::ChangeDataPtrVar GetChangeData(Bitmask64 changeBits);

    virtual void AttachObserver(Observer &observer, Bitmask64 changeBits);
    virtual void DetachObserver(Observer &observer);
    virtual Priority GetPriority() const;
    virtual I32 GetObjectId() const;

    virtual std::string GetME() { return ""; }

  private:
    std::mutex m_mutex;
    ObserverSubscriptionVec m_observerSubscriptions;
  };

  using SubjectUPtr = std::unique_ptr<Subject>;

  template <typename ChangeDataT>
  ChangeDataT GetChangeData(Subject *subject, Bitmask64 changeBits) {
    return std::get<ChangeDataT>(subject->GetChangeData(changeBits));
  }
}

#endif
