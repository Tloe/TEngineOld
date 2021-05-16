#include "TECamera.h"
#include <TEBSphere.h>
#include <TERenderable.h>
#include <TEVector3D.h>

TE::SceneGraph::Renderable::Renderable() {
}

void TE::SceneGraph::Renderable::UpdateWorldBound() {
    m_bounding.m_center = m_worldTransform.GetTranslation();
}

/*void TE::SceneGraph::Renderable::UpdateRenderStateLocal( std::stack< Memory::Pointer0< GlobalState > >* stateStack, std::vector<LightPtr>* lightStack )
{
        for (unsigned i = 0; i < GlobalState::STATE_COUNT ; i++)
        {
                m_localStates[i] = stateStack[i].top();
                assert(m_localStates[i]);
        }

        m_lights.clear();
        m_lights.insert(m_lights.begin(),lightStack->begin(), lightStack->end());
}
*/

void TE::SceneGraph::Renderable::GetRenderListNoCull(RenderablePtrList &renderList) {
    renderList.push_back(this);
}

void TE::SceneGraph::Renderable::GetRenderListNoSort(RenderablePtrList &renderList, Camera &camera) {
    if (!IsCulled(camera)) {
        renderList.push_back(this);
    }
}

void TE::SceneGraph::Renderable::SetMesh(Resources::ResourceHandle<Render::Mesh> &resourceHandle) {
    m_mesh = resourceHandle;
}

void TE::SceneGraph::Renderable::SetEffect(Resources::ResourceHandle<Render::Effect> &resourceHandle) {
    m_effect = resourceHandle;
}

void TE::SceneGraph::Renderable::AddTexture(Resources::ResourceHandle<Render::Texture> &resourceHandle) {
    m_textures.push_back(resourceHandle);
}

const TE::Resources::ResourceHandle<TE::Render::Mesh> &TE::SceneGraph::Renderable::GetMesh() {
    return m_mesh;
}

const TE::Resources::ResourceHandle<TE::Render::Effect> &TE::SceneGraph::Renderable::GetEffect() {
    return m_effect;
}

const TE::SceneGraph::Renderable::TextureVec &TE::SceneGraph::Renderable::GetTextures() {
    return m_textures;
}
