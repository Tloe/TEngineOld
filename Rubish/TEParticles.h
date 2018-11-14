#ifndef TEPARTICLES_H
#define TEPARTICLES_H
#include "TETriangles.h"

namespace TE
{
	namespace SceneGraph
	{
		class Particles : public TriangleMesh
		{
			Particles(float* vertices, float * sizes, bool calcNormals)
			{

			}

			virtual ~Particles()
			{

			}

		private:
			float* locations;

		};
	}
}

#endif