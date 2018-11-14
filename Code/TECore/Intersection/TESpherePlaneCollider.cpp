#include <TESpherePlaneCollider.h>
#include <TEBSphere.h>
#include <TEPlane.h>
#include <TEContactSet.h>

bool TE::Intersection::SpherePlaneCollider::Collide( const BSphere& bsphere, const Plane& plane, bool coarse, bool symetric, ContactSet* contacts /*= NULL*/ )
{
	F32 dist = Dot(bsphere.m_center, plane.m_normal) - Dot(plane.m_normal,plane.m_center);

	bool intersects = Math::Base<Real>::Abs(dist) <= bsphere.m_radius;

	if (!coarse && intersects)
	{
		if (symetric)
			contacts->normals.push_back(plane.m_normal);
		else
			contacts->normals.push_back(-plane.m_normal);
		contacts->penetrations.push_back(bsphere.m_radius - dist);
		contacts->points.push_back(bsphere.m_center + (plane.m_normal * dist));
	}

	return intersects;
}
