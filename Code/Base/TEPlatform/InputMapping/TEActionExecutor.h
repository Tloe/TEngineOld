#ifndef TEACTIONEXECUTOR_H
#define TEACTIONEXECUTOR_H

#include "TEDataTypes.h"

#include <memory>
#include <string>

namespace TE::InputMapping {
  class ActionExecutor {
  public:
    friend class InputMapper;

    ActionExecutor(const std::string &actionName);
    virtual ~ActionExecutor();

    virtual void Execute() = 0;

  private:
    Hash m_nameHash;
  };

  using ActionExecutorUPtr = std::unique_ptr<ActionExecutor>;
}

#endif
