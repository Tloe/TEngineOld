#ifndef TEWIREFRAME_H
#define TEWIREFRAME_H

#include <TEGlobalState.h>

namespace TE
{
	namespace SceneGraph
	{
		struct Wireframe : public GlobalState
		{
			Wireframe()
			{
				s_default[STATE_WIREFRAME].reset(new0 Wireframe);
			}

			virtual ~Wireframe()
			{

			}

			virtual I32 GetGlobalStateType() const
			{
				return STATE_WIREFRAME;
			}

			bool m_enabled;
		};
	}
}

#endif