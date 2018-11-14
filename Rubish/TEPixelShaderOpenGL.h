#ifndef TEPIXELSHADEROPENGL_H
#define TEPIXELSHADEROPENGL_H

#include <memory>
#include "TEAPIResource.h"

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
			APIPixelShader(APIContext& context, const PixelShader& pixelShader);

			~APIPixelShader();

			void Enable(APIContext& context);

			void Disable(APIContext& context);
		};
	}
}

#endif