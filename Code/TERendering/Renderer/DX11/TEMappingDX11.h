#ifndef TEMAPPINGDX11_H
#define TEMAPPINGDX11_H

#include <string>
#include <d3d11.h>

namespace TE
{
	namespace Render
	{
		class APIMapping
		{
		public:
			static const std::string s_layoutSemantic[];
			static const DXGI_FORMAT s_layoutFormat[];
			static const D3D11_INPUT_CLASSIFICATION s_layoutTypeOfData[];
			static const D3D11_PRIMITIVE_TOPOLOGY s_primitiveType[];
			static const D3D11_USAGE s_bufferUsage[];
		};
	}
}

#endif