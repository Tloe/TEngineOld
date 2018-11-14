#ifndef TECULLSTATE_H
#define TECULLSTATE_H

#include <TEGlobalState.h>

namespace TE
{
	namespace SceneGraph
	{
		struct CullState : public GlobalState
		{
			enum
			{
				FRONT_CCW,
				FRONT_CW,
				FRONT_COUNT
			};

			enum
			{
				CULLTYPE_FRONT,
				CULLTYPE_BACK,
				CULLTYPE_COUNT
			};

			CullState() : m_enabled(true), m_frontface(FRONT_CCW), m_cullface(CULLTYPE_BACK)
			{
				s_default[STATE_CULL].reset(new0 CullState);
			}

			virtual ~CullState()
			{

			}

			virtual I32 GetGlobalStateType() const
			{
				return STATE_CULL;
			}

			bool m_enabled;
			I32 m_frontface;
			I32 m_cullface;
		};
	}
}

#endif