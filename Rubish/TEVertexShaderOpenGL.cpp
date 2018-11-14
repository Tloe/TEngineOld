#include <TEVertexShaderOpenGL.h>

TE::Render::APIVertexShader::APIVertexShader( Render::APIContext& context, const VertexShader& vertexShader, APIBufferLayout& apiLayout )
{

}

TE::Render::APIVertexShader::~APIVertexShader()
{

}

void TE::Render::APIVertexShader::Enable( APIContext& context )
{
	cgGLBindProgram(m_program);
	CgGLDisableProfile(CG_PROFILE_ARBVP1);
}

void TE::Render::APIVertexShader::Disable( APIContext& context )
{

}
