#include "TERendererOpenGL.h"
#include "TEApiContextIncludes.h"
#include "TEApiResourcesIncludes.h"
#include "TEColor.h"
#include "TEEffect.h"
#include "TEMatrix4D.h"

#include <assert.h>

TE::Render::APIRenderer::APIRenderer(Platform::OSWinId osWinId, IO::FileIO &fileIO)
    : m_apiContext(osWinId, fileIO) {
    m_threadId = std::this_thread::get_id();
}

TE::Render::APIRenderer::APIRenderer(IO::FileIO &fileIO)
    : m_apiContext(fileIO) {
    m_threadId = std::this_thread::get_id();
}

TE::Render::APIRenderer::~APIRenderer() {
}

void TE::Render::APIRenderer::Initialize(/*CGcontext& cgContext*/) {
    assert(m_threadId == std::this_thread::get_id() && "Renderer can only be used in the same thread as it was initialized in");

    // m_apiContext.SetCGContext(cgContext);
    m_apiContext.Initialize();
    glewInit();
    SetViewPort(0, 0, 640, 480);
    glEnable(GL_DEPTH_TEST);
    assert(glGetError() == GL_NO_ERROR);
    glFrontFace(GL_CW);
    assert(glGetError() == GL_NO_ERROR);
    glEnable(GL_CULL_FACE);
    assert(glGetError() == GL_NO_ERROR);
}

void TE::Render::APIRenderer::Cleanup() {
    assert(m_threadId == std::this_thread::get_id() && "Renderer can only be used in the same thread as it was initialized in");

    m_apiContext.Cleanup();
}

void TE::Render::APIRenderer::BeginFrame(const ColorRGBA &clearColor) {
    assert(m_threadId == std::this_thread::get_id() && "Renderer can only be used in the same thread as it was initialized in");

    m_apiContext.BeginFrame();

    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    assert(glGetError() == GL_NO_ERROR);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    assert(glGetError() == GL_NO_ERROR);
}

void TE::Render::APIRenderer::EndFrame() {
    assert(m_threadId == std::this_thread::get_id() && "Renderer can only be used in the same thread as it was initialized in");

    m_apiContext.EndFrame();
}

void TE::Render::APIRenderer::Draw(I32 indexCount) {
    assert(m_threadId == std::this_thread::get_id() && "Renderer can only be used in the same thread as it was initialized in");

    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_SHORT, 0);
    assert(glGetError() == GL_NO_ERROR);
}

void TE::Render::APIRenderer::SetResolution(I32 width, I32 height, I32 viewportWidth, I32 viewportHeight, bool fullscreen, bool updateViewport, I32 positionX, I32 positionY) {
    assert(m_threadId == std::this_thread::get_id() && "Renderer can only be used in the same thread as it was initialized in");

    m_apiContext.SetResolution(fullscreen, width, height, 32, positionX, positionY);

    if (updateViewport)
        SetViewPort(0, 0, viewportWidth, viewportHeight);
}

void TE::Render::APIRenderer::SetViewPort(I32 x, I32 y, I32 width, I32 height) {
    assert(m_threadId == std::this_thread::get_id() && "Renderer can only be used in the same thread as it was initialized in");

    glViewport(x,
               m_apiContext.GetWindowHeight() - height - y,
               width,
               height);
    assert(glGetError() == GL_NO_ERROR);
}

TE::Render::APIVertexBufferLayoutUPtr TE::Render::APIRenderer::CreateAPIVertexBufferLayout(const Mesh &mesh, const Effect &effect) {
    assert(m_threadId == std::this_thread::get_id() && "Renderer can only be used in the same thread as it was initialized in");

    return std::make_unique<APIVertexBufferLayout>(mesh, effect);
}

TE::Render::APIVertexBufferUPtr TE::Render::APIRenderer::CreateAPIVertexBuffer(const Mesh &mesh) {
    assert(m_threadId == std::this_thread::get_id() && "Renderer can only be used in the same thread as it was initialized in");

    return std::make_unique<APIVertexBuffer>(mesh);
}

TE::Render::APIIndexBufferUPtr TE::Render::APIRenderer::CreateAPIIndexBuffer(const Mesh &mesh) {
    assert(m_threadId == std::this_thread::get_id() && "Renderer can only be used in the same thread as it was initialized in");

    return std::make_unique<APIIndexBuffer>(mesh);
}

TE::Render::APITexture2DUPtr TE::Render::APIRenderer::CreateAPITexture2D(Texture &texture, Effect &effect) {
    assert(m_threadId == std::this_thread::get_id() && "Renderer can only be used in the same thread as it was initialized in");

    return std::make_unique<APITexture2D>(texture);
}

TE::Platform::PlatformWindow &TE::Render::APIRenderer::GetPlatformWindow() {
    return m_apiContext;
}
