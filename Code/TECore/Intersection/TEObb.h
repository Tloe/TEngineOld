#ifndef TEOBB_H
#define TEOBB_H

#include <TEVector3D.h>
#include <vector>
#include <TEDataTypes.h>

namespace TE
{
	namespace Math { template<typename T> class Quaternion; }

	namespace Intersection
	{
		struct Obb
		{
			Obb(){}
			Obb(const Math::Vector3D<Real> &center, const Math::Vector3D<Real> axes[], const Math::Vector3D<Real> &extents);
			Obb(const Obb &rhs);
			Obb& operator=(const Obb& rhs);

			Math::Vector3D<Real> m_axes[3];
			Math::Vector3D<Real> m_extents;
			Math::Vector3D<Real> m_center;
		};

		void Rotate(Obb &obb,Math::Quaternion<Real> &orientation);
		Real GetGrowth(Obb &obb0, Obb &obb1);
		void Grow(Obb& obb, const Obb& other);
		void ObbFromVertexData(Obb& obb, const F32 *vertexData, unsigned vDataCount);
		Math::Vector3D<Real> FindNearestPointOnObb(const Obb& obb,const Math::Vector3D<Real> &p);
		Math::Vector3D<Real> GetPointFromIndex(const Obb& obb, I32 index);
	}
}

#endif