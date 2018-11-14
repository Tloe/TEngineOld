#ifndef TEPLANE_H
#define TEPLANE_H

#include <TEDataTypes.h>
#include <TEVector3D.h>

namespace TE
{
	namespace Intersection { struct BSphere; }

	namespace Intersection
	{
		struct Plane 
		{
			Plane(){}
			Plane(const Math::Vector3D<Real> &center, const Math::Vector3D<Real> &normal) : m_center(center), m_normal(normal) {};
			Plane(const Plane &rhs) : m_center(rhs.m_center), m_normal(rhs.m_normal){}
			Plane& operator=(const Plane & rhs);
				
			Math::Vector3D<Real> m_center;
			Math::Vector3D<Real> m_normal;
		};

		I32 WhichSide(const Plane& plane, const BSphere& bsphere);
	}
}
#endif