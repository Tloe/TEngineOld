#ifndef TERENDERABLE_H
#define TERENDERABLE_H

#include "TEDataTypes.h"
#include "TEEffect.h"
#include "TEJson.h"
#include "TEMesh.h"
#include "TEResource.h"
#include "TETexture.h"
#include <TEResourceManager.h>
#include <TESpatial.h>

#include <map>
#include <vector>

namespace TE::SceneGraph {
  class Camera;

  class Renderable : public Spatial {
  public:
    using TextureVec = std::vector<Resources::ResourceHandle<Render::Texture>>;

    Renderable();

    virtual void GetRenderListNoCull(RenderablePtrList &renderList);
    virtual void GetRenderListNoSort(RenderablePtrList &renderList, Camera &camera);

    void SetMesh(Resources::ResourceHandle<Render::Mesh> &resourceHandle);
    void SetEffect(Resources::ResourceHandle<Render::Effect> &resourceHandle);
    void AddTexture(Resources::ResourceHandle<Render::Texture> &resourceHandle);

    const Resources::ResourceHandle<Render::Mesh> &GetMesh();
    const Resources::ResourceHandle<Render::Effect> &GetEffect();
    const TextureVec &GetTextures();

  protected:
    // virtual void UpdateRenderStateLocal(std::stack< Memory::Pointer0< GlobalState > >*
    // stateStack, std::vector<LightPtr>* lightStack);
  private:
    virtual void UpdateWorldBound();

    Resources::ResourceHandle<Render::Mesh> m_mesh;
    Resources::ResourceHandle<Render::Effect> m_effect;
    TextureVec m_textures;

    // Memory::Pointer0<GlobalState> m_localStates[GlobalState::STATE_COUNT];
    // std::vector<LightPtr> m_lights;
  };
}

#endif
