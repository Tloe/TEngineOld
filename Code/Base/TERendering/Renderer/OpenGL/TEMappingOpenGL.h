#ifndef TEMAPPINGOPENGL_H
#define TEMAPPINGOPENGL_H

#include "TEOpenGL.h"

#include <string>

namespace TE
{
	namespace Render
	{
		class APIMapping
		{
		public:
			static const GLuint	s_dataType[];
			static const GLuint s_usage[];
			static const GLuint s_primitiveType[];
			static const GLuint s_semantics[];
			static const GLuint s_colorType[];
		};
	}
}

#endif
