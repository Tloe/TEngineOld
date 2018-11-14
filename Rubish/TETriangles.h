#ifndef TETRIANGLEMESH_H
#define TETRIANGLEMESH_H
#include "TERenderable.h"

namespace TE
{
	namespace SceneGraph
	{
		class Triangles : public Renderable
		{
		public:
		private:
		};


		class TriangleFan : public Triangles
		{

		};

		class TriangleMesh : public Triangles
		{

		};

		class TriangleStrip: public Triangles
		{

		};
	}
}

#endif