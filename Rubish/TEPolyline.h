#ifndef POLYLINE_H
#define POLYLINE_H

#include "TERenderable.h"

namespace TE
{
	namespace SceneGraph
	{
		class Polyline : public Renderable
		{
		public:
			Polyline(float* vertices, bool closed, bool contiguous);

			void SetActiveCount(int activeCount);

			int GetActiveCount();

			void SetClosed(bool closed);

			bool GetClosed();

			void SetContigous(bool contigous);

			bool GetContigous();

			virtual ~Polyline();
		private:
			void UpdatePrimitiveType();

			int			m_activeCount;
			bool		m_closed;
			bool		m_contigous;
		};
	}
}

#endif