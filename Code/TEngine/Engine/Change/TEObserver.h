#ifndef TEOBSERVER_H
#define TEOBSERVER_H

#include "TEDataTypes.h"

#include <memory>

namespace TE::Engine {
  class Subject;
  class Observer {
  public:
    virtual ~Observer() {}
    virtual void OnSubjectChange(Subject *subject, Bitmask64 changeBits) = 0;
  };

  using ObserverUPtr = std::unique_ptr<Observer>;
}

#endif
