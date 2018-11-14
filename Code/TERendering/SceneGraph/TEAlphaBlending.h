#ifndef TEALPHABLENDING_H
#define TEALPHABLENDING_H

#include <TEGlobalState.h>

namespace TE
{
	namespace SceneGraph
	{
		struct AlphaBlending : public GlobalState
		{
			enum
			{
				SOURCE_ZERO,
				SOURCE_ONE,
				SOURCE_DST_COLOR,
				SOURCE_ONE_MINUS_DST_COLOR,
				SOURCE_SRC_ALPHA,
				SOURCE_ONE_MINUS_SRC_ALPHA,
				SOURCE_DST_ALPHA,
				SOURCE_ONE_MINUS_DST_ALPHA,
				SOURCE_SRC_ALPHA_SATURATE,
				SOURCE_CONSTANT_COLOR,
				SOURCE_ONE_MINUS_CONSTANT_COLOR,
				SOURCE_CONSTANT_ALPHA,
				SOURCE_ONE_MINUS_CONSTANT_ALPHA,
				SOURCE_COUNT
			};

			enum
			{
				DESTINATION_ZERO,
				DESTINATION_ONE,
				DESTINATION_SRC_COLOR,
				DESTINATION_ONE_MINUS_SRC_COLOR,
				DESTINATION_SRC_ALPHA,
				DESTINATION_ONE_MINUS_SRC_ALPHA,
				DESTINATION_DST_ALPHA,
				DESTINATION_ONE_MINUS_DST_ALPHA,
				DESTINATION_CONSTANT_COLOR,
				DESTINATION_ONE_MINUS_CONSTANT_COLOR,
				DESTINATION_CONSTANT_ALPHA,
				DESTINATION_ONE_MINUS_CONSTANT_ALPHA,
				DESTINATION_COUNT
			};

			enum
			{
				ALPHATEST_NEVER,
				ALPHATEST_LESS,
				ALPHATEST_EQUAL,
				ALPHATEST_LEQUAL,
				ALPHATEST_GREATER,
				ALPHATEST_NOTEQUAL,
				ALPHATEST_GEQUAL,
				ALPHATEST_ALWAYAS,
				ALPHATEST_COUNT
			};

			AlphaBlending()
				:
				m_blendEnabled(false),
				m_alphaTestEnabled(false),
				m_sourceBlend(SOURCE_SRC_ALPHA),
				m_destinationBlend(DESTINATION_ONE_MINUS_SRC_ALPHA),
				m_alphaTest(ALPHATEST_ALWAYAS),
				m_reference(Math::Base<Real>::REAL_ZERO)
			{
				s_default[STATE_ALPHA].reset(new0 AlphaBlending);
			}

			bool m_blendEnabled;
			bool m_alphaTestEnabled;
			I32 m_sourceBlend;
			I32 m_destinationBlend;
			I32 m_alphaTest;
			Real m_reference;
		};
	}
}

#endif