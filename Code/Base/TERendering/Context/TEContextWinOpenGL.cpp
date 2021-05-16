#include "TEContextWinOpenGL.h"
#include "OpenGL/TEOpenGL.h"
#include "TEPlatformWindowIncludes.h"

#include <assert.h>
#include <windows.h>

TE::Context::APIContext::APIContext(Platform::OSWinId osWinId, IO::FileIO &fileIO, const std::string &windowName /*= "TEngine"*/)
    : PlatformWindow(osWinId, fileIO, windowName) {
}

TE::Context::APIContext::APIContext(IO::FileIO &fileIO, const std::string &windowName /*= "TEngine"*/)
    : PlatformWindow(fileIO, windowName) {
}

TE::Context::APIContext::~APIContext() {
}

void TE::Context::APIContext::SetCGContext(/*CGcontext& cgContext*/) {
    // m_cgContext = cgContext;
}

void TE::Context::APIContext::OnOpenWindow() {
    PIXELFORMATDESCRIPTOR pfd;
    I32 format;

    // get the device context (DC)
    m_hdc = GetDC(GetHWND());

    // set the pixel format for the DC
    ZeroMemory(&pfd, sizeof(pfd));
    pfd.nSize      = sizeof(pfd);
    pfd.nVersion   = 1;
    pfd.dwFlags    = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    format         = ChoosePixelFormat(m_hdc, &pfd);
    SetPixelFormat(m_hdc, format, &pfd);

    // create and enable the render context (RC)
    m_hrcs.push_back(HGLRC());
    m_hrcs[0] = wglCreateContext(m_hdc);
    assert(wglMakeCurrent(m_hdc, m_hrcs[0]));
    assert(glGetError() == GL_NO_ERROR);

    /*cgGLSetDebugMode(CG_FALSE);
    cgGLRegisterStates(m_cgContext);
    cgGLSetManageTextureParameters(m_cgContext, CG_TRUE);*/
}

void TE::Context::APIContext::OnCloseWindow() {
    wglMakeCurrent(NULL, NULL);
    for (U32 i = 0; i < m_hrcs.size(); ++i) {
        if (m_hrcs[i]) {
            wglDeleteContext(m_hrcs[i]);
        }
    }
}

void TE::Context::APIContext::BeginFrame() {
}

void TE::Context::APIContext::EndFrame() {
    SwapBuffers(m_hdc);
}
