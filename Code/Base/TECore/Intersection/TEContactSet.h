#ifndef TECONTACTSET_H
#define TECONTACTSET_H

#include <vector>
#include <TEVector3D.h>

namespace TE
{
	namespace Intersection
	{
		struct ContactSet
		{
			std::vector<Math::Vector3D<Real> > points;
			std::vector<Real> penetrations;
			std::vector<Math::Vector3D<Real> > normals;
		};
	}
}

#endif
