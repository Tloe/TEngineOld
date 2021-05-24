#ifndef TENODE_H
#define TENODE_H

#include <TESpatial.h>
#include <list>

namespace TE::SceneGraph {
  class Camera;

  class Node : public Spatial {
  public:
    Node();
    virtual ~Node();
    void GetRenderListNoCull(RenderablePtrList &renderList);
    void GetRenderListNoSort(RenderablePtrList &renderList, Camera &camera);

    void AddChild(Spatial &child);
    void RemoveChild(Spatial &child);
    void RemoveFromParrent();

  protected:
    // virtual void UpdateRenderStateLocal(std::stack< Memory::Pointer0< GlobalState > >*
    // stateStack, std::vector< Memory::Pointer0< Light > >* lightStack);
    virtual void UpdateWorldData();
    virtual void UpdateWorldBound();

  private:
    typedef std::list<Spatial *> SpatialPtrList;

    SpatialPtrList m_children;
  };
}

#endif
