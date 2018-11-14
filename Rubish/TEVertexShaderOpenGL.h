#ifndef TEVERTEXSHADEROPENGL_H
#define TEVERTEXSHADEROPENGL_H
#include "TEAPIResource.h"

namespace TE
{
	//Forward declarations
	namespace Render { class APIBufferLayout; }
	namespace Render { class VertexShader; }
	namespace Render { struct APIContext; }
	//End forward declarations

	namespace Render
	{
		class APIVertexShader : public APIResource
		{
		public:
			APIVertexShader(Render::APIContext& context, const VertexShader& vertexShader, APIBufferLayout& apiLayout);

			~APIVertexShader();

			void Enable(APIContext& context);

			void Disable(APIContext& context);
		private:
		};
	}
}

#endif