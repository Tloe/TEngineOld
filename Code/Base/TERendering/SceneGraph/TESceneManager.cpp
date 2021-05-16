#include "TESceneManager.h"
#include "TECamera.h"
#include "TEEffect.h"
#include "TEMesh.h"
#include "TENode.h"
#include "TERenderable.h"
#include "TERenderer.h"
#include "TEResourceHandle.h"
#include "TESpatial.h"
#include "TETexture.h"

TE::SceneGraph::SceneManager::SceneManager(Render::Renderer &renderer)
    : m_renderer(renderer) {
}

void TE::SceneGraph::SceneManager::DrawScene(F32 interpolation) {
    m_renderer.BeginFrame();

    // Get renderables from scenegraph
    std::list<TE::SceneGraph::Renderable *> renderables;
    m_rootNode.GetRenderListNoCull(renderables);

    // Set viewProjection matrix
    for (auto &renderable : renderables) {
        DrawRenderable(*renderable);
    }

    m_renderer.EndFrame();
}

void TE::SceneGraph::SceneManager::DrawRenderable(SceneGraph::Renderable &renderable) {
    auto &meshHandle    = renderable.GetMesh();
    auto &textureHandle = renderable.GetTextures()[0];
    auto &effectHandle  = renderable.GetEffect();

    m_renderer.SetViewProjectionMatrix(m_activeCamera->GetViewProjectionMatrix(), *effectHandle);
    m_renderer.SetModelMatrix(renderable.GetTransformMatrix(), *effectHandle);

    m_renderer.EnableAPIMesh(*meshHandle);
    m_renderer.EnableAPITexture(*textureHandle, *effectHandle);

    U32 indexCount = meshHandle->GetIndexBufferInfo().dataElementCount;
    while (m_renderer.SetNextPass(*effectHandle)) {
        m_renderer.Draw(indexCount);
    }
    m_renderer.DisableAPIMesh(*meshHandle);
    m_renderer.DisableAPITexture(*textureHandle);
}

void TE::SceneGraph::SceneManager::InitRenderable(SceneGraph::Renderable &renderable) {
    auto &meshHandle    = renderable.GetMesh();
    auto &textureHandle = renderable.GetTextures()[0];
    auto &effectHandle  = renderable.GetEffect();

    m_renderer.InitEffect(*effectHandle);
    m_renderer.InitAPIMesh(*meshHandle, *effectHandle);
    m_renderer.InitAPITexture(*textureHandle, *effectHandle);
}

void TE::SceneGraph::SceneManager::CleanupRenderable(SceneGraph::Renderable &renderable) {
    auto &meshHandle    = renderable.GetMesh();
    auto &textureHandle = renderable.GetTextures()[0];
    auto &effectHandle  = renderable.GetEffect();

    m_renderer.CleanupAPIMesh(*meshHandle);
    m_renderer.CleanupEffect(*effectHandle);
    m_renderer.CleanupAPITexture(*textureHandle);
}

void TE::SceneGraph::SceneManager::SetActiveCamera(SceneGraph::Camera &camera) {
    m_activeCamera = &camera;
}

TE::Render::Renderer &TE::SceneGraph::SceneManager::GetRenderer() {
    return m_renderer;
}

void TE::SceneGraph::SceneManager::AddToRootNode(Spatial &spatial) {
    m_rootNode.AddChild(spatial);
}

void TE::SceneGraph::SceneManager::AddToNode(const std::string &parrent, SceneGraph::Node &node) {
    assert(parrent == "Root" || m_nodeMap.find(parrent) != m_nodeMap.end());

    if (parrent == "Root") {
        m_rootNode.AddChild(node);
    } else {
        m_nodeMap.insert(std::make_pair(parrent, &node));
        m_nodeMap[parrent]->AddChild(node);
    }
}

void TE::SceneGraph::SceneManager::AddToNode(const std::string &parrent, SceneGraph::Renderable &renderable) {
    assert(parrent == "Root" || m_nodeMap.find(parrent) != m_nodeMap.end());

    if (parrent == "Root") {
        m_rootNode.AddChild(renderable);
    } else {
        m_nodeMap[parrent]->AddChild(renderable);
    }
}
