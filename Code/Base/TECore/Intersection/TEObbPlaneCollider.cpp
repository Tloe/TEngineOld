#include <TEContactSet.h>
#include <TEMathBase.h>
#include <TEObb.h>
#include <TEObbPlaneCollider.h>
#include <TEPlane.h>

bool TE::Intersection::ObbPlaneCollider::Collide(const Obb &obb,
                                                 const Plane &plane,
                                                 bool coarse,
                                                 bool symetric,
                                                 ContactSet *contacts) {
    // WARNING! Does not produce the correct contact points!

    F32 r = obb.m_extents[0] * Math::Base<Real>::Abs(Dot(plane.m_normal, obb.m_axes[0])) +
            obb.m_extents[1] * Math::Base<Real>::Abs(Dot(plane.m_normal, obb.m_axes[1])) +
            obb.m_extents[2] * Math::Base<Real>::Abs(Dot(plane.m_normal, obb.m_axes[2]));

    F32 s          = Dot(plane.m_normal, obb.m_center) - Dot(plane.m_normal, plane.m_center);

    bool collision = Math::Base<Real>::Abs(s) <= r;
    if (collision && !coarse) {
        if (symetric)
            contacts->normals.push_back(plane.m_normal);
        else
            contacts->normals.push_back(-plane.m_normal);
        F32 penetration = Math::Base<Real>::Abs(r) - Math::Base<Real>::Abs(s);
        contacts->penetrations.push_back(penetration);
        contacts->points.push_back(
            obb.m_center + (-plane.m_normal * (Math::Base<Real>::Abs(r) - (penetration * 0.5f))));
    }

    return collision;
}
