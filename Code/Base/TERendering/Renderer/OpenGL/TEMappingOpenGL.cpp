#include <TEMappingOpenGL.h>

const GLuint TE::Render::APIMapping::s_primitiveType[] = {GL_POINTS, GL_LINES, GL_LINE_STRIP,
                                                          GL_TRIANGLES, GL_TRIANGLE_STRIP};

const GLuint TE::Render::APIMapping::s_usage[]         = {GL_STATIC_DRAW, GL_DYNAMIC_DRAW};

const GLuint TE::Render::APIMapping::s_dataType[]      = {
    GL_FLOAT, GL_FLOAT, GL_FLOAT, GL_FLOAT, GL_SHORT,
};

const GLuint TE::Render::APIMapping::s_semantics[] = {0, 1, 2,  3,  4,  5,  6,  7,
                                                      8, 9, 10, 11, 12, 13, 14, 15};

const GLuint TE::Render::APIMapping::s_colorType[] = {GL_RGB, GL_RGBA};
