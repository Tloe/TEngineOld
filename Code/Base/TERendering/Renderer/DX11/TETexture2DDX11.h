#ifndef TETEXTURE2DDX11_H
#define TETEXTURE2DDX11_H

#include "TEDataTypes.h"

//#include "Cg/cg.h"

#include <memory>


struct ID3D11ShaderResourceView;
struct ID3D11SamplerState;
struct ID3D11Texture2D;

namespace TE
{
	namespace Render { class Texture; }
	namespace Context { class APIContext; }

	namespace Render
	{
		class APITexture2D
		{
		public:
			APITexture2D(Context::APIContext& context, Texture& texture, CGparameter cgParameter);
			~APITexture2D();
			void Enable(CGparameter cgParameter);
            void Disable();
            U32 IncreaseUsageCount();
            U32 DecreaseUsageCount();

        private:
            U32 m_usageCount;
			ID3D11Texture2D* m_d3dTexture;
			//ID3D11ShaderResourceView* m_pD3DTextureRV;
			//ID3D11SamplerState* m_pD3DSamplerLinear;
		};

		typedef std::unique_ptr<APITexture2D> APITexture2DUPtr;
	}
}

#endif
