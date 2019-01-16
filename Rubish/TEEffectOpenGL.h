#ifndef TEEFFECTOPENGL_H
#define TEEFFECTOPENGL_H

#include "TEAPIResource.h"
#include <memory>
#include "Cg/cg.h"

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
			APIEffect(APIContext& context, /*CGcontext& cgContext,*/ Effect& effect);
			~APIEffect();
			void Enable(APIContext& context);
			void Disable(APIContext& context);
		private:
		};
	}
}

#endif
