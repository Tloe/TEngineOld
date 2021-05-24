#ifndef TEGRAPHICSSCENE_H
#define TEGRAPHICSSCENE_H

#include "TEGraphicsTask.h"
#include "TESceneManager.h"
#include "TESystemScene.h"

#include <map>

namespace TE::Engine {
  class SystemObject;
}

namespace TE::Graphics {
  class GraphicsScene : public Engine::SystemScene {
  public:
    GraphicsScene(SceneGraph::SceneManager &sceneManager);

    virtual void Initialize();
    virtual void Cleanup();
    virtual Engine::SystemTask *GetSystemTask();
    virtual Engine::SystemObjectSPtr CreateSystemObject(const std::string &objectType,
                                                        I32 objectId);

  private:
    SceneGraph::SceneManager &m_sceneManager;
    GraphicsTask m_graphicsTask;
  };
}

#endif
