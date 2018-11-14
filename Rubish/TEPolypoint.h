#ifndef TEPOINTS_H
#define TEPOINTS_H

#include <TERenderable.h>

namespace TE
{
	namespace SceneGraph
	{
		class Polypoint : public Renderable
		{
		public:
			Polypoint(float* vertices);

			void SetActiveCount(int activeCount);

			int GetActiveCount();
		private:
			int m_activeCount;
		};
	}
}

#endif