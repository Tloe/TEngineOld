#ifndef TERENDERABLEOBJECT_H
#define TERENDERABLEOBJECT_H

#include "TEChangeMasks.h"
#include "TEDataTypes.h"
#include "TEGraphicsObject.h"
#include "TEJson.h"
#include "TERenderable.h"

#include <unordered_map>

namespace TE::SceneGraph {
  class SceneManager;
}

namespace TE::Graphics {
  class SceneGraphBuilder;

  class RenderableObject : public GraphicsObject {
  public:
    struct Values {
      enum { Mesh, Texture, Effect, BoundingVolume, Parrent };
    };

    RenderableObject(I32 objectId, SceneGraph::SceneManager &sceneManager);
    ~RenderableObject();

    virtual void SetValue(Core::Value &value);
    virtual void Initialize();
    virtual void Cleanup();
    /*			virtual void JSONDeserialize(const Json::Value& jsonValue);
                            virtual void JSONSerialize(Json::Value& jsonValue);*/
    virtual void OnSubjectChange(Subject *subject, Bitmask64 changeBits);

  private:
    SceneGraph::SceneManager &m_sceneManager;
    SceneGraph::Renderable m_renderable;
  };
}

#endif
