#include "TEContextLinuxOpenGL.h"
#include "TELinuxWindow.h"

#include <cstdlib>
#include <iostream>


TE::Context::APIContext::APIContext(Platform::OSWinId osWinId, IO::FileIO & fileIO, const std::string& windowName)
    : PlatformWindow(osWinId, fileIO, windowName)
    , m_xlibVisualInfo(nullptr)
{

}

TE::Context::APIContext::APIContext(IO::FileIO & fileIO, const std::string& windowName)
    : PlatformWindow(fileIO, windowName)
    , m_xlibVisualInfo(nullptr)
{

}

TE::Context::APIContext::~APIContext()
{
    XFree(m_xlibVisualInfo);
}

void TE::Context::APIContext::SetCGContext(/*CGcontext &cgContext*/)
{
    /* m_cgContext = cgContext; */
}

void TE::Context::APIContext::OnOpenWindow()
{
    m_xlibWindowXID = GetWindowXID();
    m_glContext = glXCreateContext(GetDisplay(),
                                   GetVisualInfo(),
                                   nullptr,
                                   GL_TRUE);
    glXMakeCurrent(GetDisplay(),
                   GetWindowXID(),
                   m_glContext);

    /* cgGLRegisterStates(m_cgContext); */
    /* cgGLSetManageTextureParameters(m_cgContext, CG_TRUE); */
}

void TE::Context::APIContext::OnCloseWindow()
{
    glXMakeCurrent(GetDisplay(), 0, NULL);
    glXDestroyContext(GetDisplay(), m_glContext);
}

XVisualInfo *TE::Context::APIContext::GetVisualInfo()
{
    assert(GetDisplay());
    if(!m_xlibVisualInfo)
    {
        GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, 0 };
        m_xlibVisualInfo = glXChooseVisual(GetDisplay(), 0, att);

        if(!m_xlibVisualInfo)
        {
            //LOG FATAL ERROR
            exit(-1);
        }
        //LOG selected visual m_xlibVisualInfo->visualid
    }

    return m_xlibVisualInfo;
}

void TE::Context::APIContext::BeginFrame()
{
	
}

void TE::Context::APIContext::EndFrame()
{
    glXSwapBuffers(GetDisplay(), m_xlibWindowXID);
}
