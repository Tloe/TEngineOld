#include <TEPlane.h>
#include <TEBSphere.h>

TE::Intersection::Plane& TE::Intersection::Plane::operator=(const TE::Intersection::Plane & rhs)
{
	if (this != &rhs)
	{
		m_center = rhs.m_center;
		m_normal = rhs.m_normal;
	}
	return *this;
}

I32 TE::Intersection::WhichSide( const Plane& plane, const BSphere& bsphere )
{
	F32 dist = Dot(bsphere.m_center,plane.m_normal) - Dot(plane.m_normal,plane.m_center);

	if (dist <= -bsphere.m_radius)
	{
		return -1;
	}

	if (dist >= bsphere.m_radius)
	{
		return +1;
	}

	return 0;
}
