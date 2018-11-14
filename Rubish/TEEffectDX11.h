#ifndef TEEFFECTDX11_H
#define TEEFFECTDX11_H

#include "TEAPIResource.h"
#include <memory>
#include "Cg/cg.h"
#include <unordered_map>

//Forward declarations
struct ID3D10Blob;
//End forward declarations

namespace TE
{
	//Forward declarations
	namespace Render { class Effect; typedef std::shared_ptr<Effect> EffectPtr; }
	namespace Render { struct APIContext; }
	//End forward declarations

	namespace Render
	{
		class APIEffect : public APIResource
		{
		public:
			APIEffect(APIContext& context, CGcontext& cgContext, const Effect& effect);
			~APIEffect();
			void Enable(APIContext& context);
			void Disable(APIContext& context);
			bool SetupNextPass();
			ID3D10Blob* GetD3DBlob() const;
		private:
			const Effect& m_effect;

		};
	}
}

#endif
