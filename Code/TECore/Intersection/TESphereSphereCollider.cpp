#include <TESphereSphereCollider.h>
#include <TEBSphere.h>
#include <TEContactSet.h>

bool TE::Intersection::SphereSphereCollider::Collide( const BSphere& bsphere0, const BSphere& bsphere1, bool coarse, ContactSet* contacts /*= NULL*/ )
{
	F32 distanceSquared = MagnitudeSqr(bsphere0.m_center - bsphere1.m_center);

	bool intersects = distanceSquared <= 
		(bsphere0.m_radius + bsphere1.m_radius) * (bsphere0.m_radius + bsphere1.m_radius);

	if (!coarse && intersects)
	{
		TE::Math::Vector3D<Real> colPt = bsphere0.m_center - ((bsphere1.m_center - bsphere0.m_center) * 0.5f);
		TE::Math::Vector3D<Real> normal = colPt - bsphere0.m_center;
		normal.Normalize();

		contacts->normals.push_back(normal);
		contacts->penetrations.push_back(-(sqrt(distanceSquared) - bsphere0.m_radius - bsphere1.m_radius));
		contacts->points.push_back(colPt);
	}

	return intersects;
}
