#ifndef TEPIXELSHADERDX11_H
#define TEPIXELSHADERDX11_H

#include "TEAPIResource.h"
#include <d3dx11async.h>
#include <memory>
#include "Cg\cg.h"

namespace TE
{
	//Forward declarations
	namespace Render { class PixelShader; typedef std::shared_ptr<PixelShader> PixelShaderPtr; }
	namespace Render { struct APIContext; }
	//End forward declarations

	namespace Render
	{
		class APIPixelShader : public APIResource
		{
		public:
			APIPixelShader(APIContext& context, CGcontext& cgContext, const PixelShader& pixelShader);

			~APIPixelShader();

			void Enable(APIContext& context);

			void Disable(APIContext& context);
		private:
			//ID3D11PixelShader *m_pPS;
			CGprogram m_cgProgram;
		};
	}
}

#endif