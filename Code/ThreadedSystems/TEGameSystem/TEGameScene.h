#ifndef TEGAMESCENE_H
#define TEGAMESCENE_H

#include "TEDataTypes.h"
#include "TEGameTask.h"
#include "TESystemObject.h"
#include "TESystemScene.h"

#include <string>

namespace TE::Engine {
  class SystemTask;

  class SystemObject;
  using SystemObjectSPtr = std::shared_ptr<SystemObject>;
}

namespace TE::Game {
  class GameScene : public Engine::SystemScene {
  public:
    GameScene();

    virtual void Initialize();
    virtual void Cleanup();

    virtual Engine::SystemTask *GetSystemTask();
    virtual Engine::SystemObjectSPtr CreateSystemObject(const std::string &objectType,
                                                        I32 objectId);

    void Update();

  private:
    GameTask m_gameTask;
  };
}

#endif
