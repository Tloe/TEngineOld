#include "TEChangeMasks.h"
#include "TEGraphicsSystem.h"
#include <TEGraphicsTask.h>
#include <TERenderer.h>
#include <TESceneManager.h>

TE::Graphics::GraphicsTask::GraphicsTask(SceneGraph::SceneManager &sceneManager)
    : m_sceneManager(sceneManager) {}

void TE::Graphics::GraphicsTask::Run() { m_sceneManager.DrawScene(m_interpolation); }

Bitmask TE::Graphics::GraphicsTask::GetTaskFlags() {
    return Engine::TaskFlags::RunInMainThread | Engine::TaskFlags::DrawingTask;
}

void TE::Graphics::GraphicsTask::SetInterpolation(F32 interpolation) {
    m_interpolation = interpolation;
}
