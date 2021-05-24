#include <TEBSphere.h>
#include <TEColliderVisitor.h>
#include <TEObb.h>
#include <TEObbObbCollider.h>
#include <TEObbPlaneCollider.h>
#include <TEPlane.h>
#include <TESphereObbCollider.h>
#include <TESpherePlaneCollider.h>
#include <TESphereSphereCollider.h>

bool TE::Intersection::ColliderVisitor::operator()(TE::Intersection::Obb &obb,
                                                   TE::Intersection::Plane &plane) {
    return TE::Intersection::ObbPlaneCollider::Collide(obb, plane, m_coarse, true, m_contactSet);
}

bool TE::Intersection::ColliderVisitor::operator()(TE::Intersection::Obb &obb,
                                                   TE::Intersection::BSphere &bsphere) {
    return TE::Intersection::SphereObbCollider::Collide(bsphere, obb, m_coarse, false,
                                                        m_contactSet);
}

bool TE::Intersection::ColliderVisitor::operator()(TE::Intersection::Obb &obb0,
                                                   TE::Intersection::Obb &obb1) {
    return TE::Intersection::ObbObbCollider::Collide(obb0, obb1, m_dt, m_coarse, true, m_pos0,
                                                     m_pos1, m_vel0, m_vel1, m_angvel0, m_angvel1,
                                                     m_contactSet);
}

bool TE::Intersection::ColliderVisitor::operator()(TE::Intersection::Plane &plane,
                                                   TE::Intersection::Obb &obb) {
    return TE::Intersection::ObbPlaneCollider::Collide(obb, plane, m_coarse, false, m_contactSet);
}

bool TE::Intersection::ColliderVisitor::operator()(TE::Intersection::Plane &plane,
                                                   TE::Intersection::BSphere &bsphere) {
    return TE::Intersection::SpherePlaneCollider::Collide(bsphere, plane, m_coarse, false,
                                                          m_contactSet);
}

bool TE::Intersection::ColliderVisitor::operator()(TE::Intersection::Plane &plane0,
                                                   TE::Intersection::Plane &plane1) {
    assert(false && "Not implemented");
    return false;
}

bool TE::Intersection::ColliderVisitor::operator()(TE::Intersection::BSphere &bsphere,
                                                   TE::Intersection::Obb &obb) {
    return TE::Intersection::SphereObbCollider::Collide(bsphere, obb, m_coarse, true, m_contactSet);
}

bool TE::Intersection::ColliderVisitor::operator()(TE::Intersection::BSphere &bsphere,
                                                   TE::Intersection::Plane &plane) {
    return TE::Intersection::SpherePlaneCollider::Collide(bsphere, plane, m_coarse, true,
                                                          m_contactSet);
}

bool TE::Intersection::ColliderVisitor::operator()(TE::Intersection::BSphere &bsphere0,
                                                   TE::Intersection::BSphere &bsphere1) {
    return TE::Intersection::SphereSphereCollider::Collide(bsphere0, bsphere1, m_coarse,
                                                           m_contactSet);
}
