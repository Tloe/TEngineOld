#ifndef TENETWORKTASK_H
#define TENETWORKTASK_H

#include "TESystemTask.h"

namespace TE::Network {
  class NetworkScene;

  class NetworkTask : public Engine::SystemTask {
  public:
    NetworkTask(NetworkScene &networkScene);

    virtual void Run(); // Return bool until msvc bug is fixed
    virtual Bitmask GetTaskFlags();
    virtual void SetDeltaValues(U64 t, U64 dt);

  private:
    NetworkScene &m_networkScene;
    U64 m_deltaTime;
    U64 m_time;
  };
}

#endif
