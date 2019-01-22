#ifndef TEZBUFFERSTATE_H
#define TEZBUFFERSTATE_H

#include <TEGlobalState.h>

namespace TE
{
	namespace SceneGraph
	{
		struct ZBufferState : public GlobalState
		{
		public:
			enum
			{
				COMPARE_NEVER,
				COMPARE_LESS,
				COMPARE_EQUAL,
				COMPARE_LEQUAL,
				COMPARE_GREATER,
				COMPARE_NOTEQUAL,
				COMPARE_GEQUAL,
				COMPARE_ALWAYS,
				COMPARE_COUNT
			};

			ZBufferState()
				:
				m_enabled(true),
				m_writable(true),
				m_compare(COMPARE_LEQUAL)
			{
				s_default[STATE_ZBUFFER].reset(new0 ZBufferState);
			}
			
			virtual ~ZBufferState()
			{}
			
			virtual I32 GetGlobalStateType() const
			{
				return STATE_ZBUFFER;
			}

			bool m_enabled;
			bool m_writable;
			I32 m_compare;
		};
	}
}

#endif