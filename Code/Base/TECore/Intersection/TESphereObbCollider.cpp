#include <TEBSphere.h>
#include <TEContactSet.h>
#include <TEObb.h>
#include <TESphereObbCollider.h>
#include <TEVector3D.h>

bool TE::Intersection::SphereObbCollider::Collide(const BSphere &bsphere,
                                                  const Obb &obb,
                                                  bool coarse,
                                                  bool symetric,
                                                  ContactSet *contacts) {
    TE::Math::Vector3D<Real> colPt = FindNearestPointOnObb(obb, bsphere.m_center);
    TE::Math::Vector3D<Real> v     = colPt - bsphere.m_center;

    bool collision                 = Dot(v, v) <= bsphere.m_radius * bsphere.m_radius;

    if (collision && !coarse) {
        TE::Math::Vector3D<Real> contactNormal = bsphere.m_center - colPt;
        contactNormal.Normalize();
        F32 penetrationDepth = bsphere.m_radius - Magnitude(v);

        if (symetric)
            contacts->normals.push_back(contactNormal);
        else
            contacts->normals.push_back(-contactNormal);
        contacts->penetrations.push_back(penetrationDepth);
        contacts->points.push_back(colPt);
    }

    return collision;
}
