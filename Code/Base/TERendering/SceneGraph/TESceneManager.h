#ifndef TESCENEMANAGER_H
#define TESCENEMANAGER_H

#include "TENode.h"
#include <string>
#include <unordered_map>

namespace TE::Render {
  class Renderer;
}

namespace TE::SceneGraph {
  class Camera;
  class Renderable;
  class Spatial;

  class SceneManager {
  public:
    SceneManager(Render::Renderer &renderer);

    void SetActiveCamera(SceneGraph::Camera &camera);

    void InitRenderable(SceneGraph::Renderable &renderable);
    void CleanupRenderable(SceneGraph::Renderable &renderable);

    void DrawScene(F32 interpolation);
    void DrawRenderable(SceneGraph::Renderable &renderable);

    void AddToRootNode(Spatial &spatial);
    void AddToNode(const std::string &parrent, SceneGraph::Node &node);
    void AddToNode(const std::string &parrent, SceneGraph::Renderable &renderable);

    Render::Renderer &GetRenderer();

  private:
    using NodeMap = std::unordered_map<std::string, SceneGraph::Node *>;

    NodeMap m_nodeMap;
    Render::Renderer &m_renderer;
    SceneGraph::Node m_rootNode;
    SceneGraph::Camera *m_activeCamera;
  };
}

#endif
