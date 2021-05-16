#include "TETexture2DOpenGL.h"
#include "TEMappingOpenGL.h"
#include "TETexture.h"

#include <assert.h>
#include <iostream>

TE::Render::APITexture2D::APITexture2D(Texture &texture /*, CGparameter cgParameter*/)
    : m_usageCount(1) {
    texture.Prepare();

    glGenTextures(1, &m_glTexture);
    assert(glGetError() == GL_NO_ERROR);

    glBindTexture(GL_TEXTURE_2D, m_glTexture);
    assert(glGetError() == GL_NO_ERROR);

    // bind the texture to the cg texture parameter
    /* cgGLSetTextureParameter(cgParameter, m_glTexture); */
    assert(glGetError() == GL_NO_ERROR);

    // initialize the state specified for a sampler parameter
    /* cgSetSamplerState(cgParameter); */
    assert(glGetError() == GL_NO_ERROR);

    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 4,
                 texture.GetImage().GetWidth(),
                 texture.GetImage().GetHeight(),
                 0,
                 APIMapping::s_colorType[texture.GetImage().GetColorType()],
                 GL_UNSIGNED_BYTE,
                 texture.GetImage().GetDataPtr());
    assert(glGetError() == GL_NO_ERROR);
}

TE::Render::APITexture2D::~APITexture2D() {
}

void TE::Render::APITexture2D::Enable(/*CGparameter cgParameter */) {
    /* cgGLSetTextureParameter(cgParameter, m_glTexture); */
    assert(glGetError() == GL_NO_ERROR);
}

void TE::Render::APITexture2D::Disable() {
    glBindTexture(GL_TEXTURE_2D, 0);

    assert(glGetError() == GL_NO_ERROR);
}

U32 TE::Render::APITexture2D::IncreaseUsageCount() {
    return ++m_usageCount;
}

U32 TE::Render::APITexture2D::DecreaseUsageCount() {
    return --m_usageCount;
}
