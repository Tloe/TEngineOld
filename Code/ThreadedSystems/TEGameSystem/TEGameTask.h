#ifndef TEGAMETASK_H
#define TEGAMETASK_H

#include "TESystemTask.h"

namespace TE::Game {
  class GameScene;

  class GameTask : public Engine::SystemTask {
  public:
    GameTask(GameScene &gameScene);

    virtual void Run();
    virtual Bitmask GetTaskFlags();
    virtual void SetInterpolation(F32 interpolation);
    virtual void SetDeltaValues(U64 t, U64 dt);

  private:
    GameScene &m_gameScene;
  };
}

#endif
