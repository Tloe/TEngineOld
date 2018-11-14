#ifndef TEVERTEXSHADERDX11_H
#define TEVERTEXSHADERDX11_H

#include <memory>
#include "TEAPIResource.h"
#include "Cg/cg.h"

//Forward declarations
struct ID3D11VertexShader;
struct ID3D10Blob;
//End forward declarations

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
			APIVertexShader(Render::APIContext& context, CGcontext& cgContext, const VertexShader& vertexShader);

			~APIVertexShader();

			void Enable(APIContext& context);
			void Disable(APIContext& context);
						
			ID3D10Blob* GetBlob() const; //Remember to call ->Release() when done using blob , use a smart pointer with custom deleter?
		private:
			//ID3D11VertexShader *m_pVS;
			CGprogram m_cgProgram;
		};

		typedef std::shared_ptr<APIVertexShader> APIVertexShaderPtr;
	}
}

#endif