#ifndef TEBSPHERE_H
#define TEBSPHERE_H

#include <TEVector3D.h>

namespace TE::Intersection {
    struct BSphere {
        BSphere() {}
        BSphere(const Math::Vector3D<Real> &center, Real radius)
            : m_center(center),
              m_radius(radius) {}
        BSphere(const BSphere &rhs) : m_center(rhs.m_center), m_radius(rhs.m_radius) {}
        BSphere &operator=(const BSphere &rhs);

        Math::Vector3D<Real> m_center;
        Real m_radius;
    };

    void BSphereFromVertexData(BSphere &bsphere, const F32 *vertexData, unsigned vDataCount);
    Real Size(const BSphere &bsphere);

    void RitterEigenSphere(BSphere &bsphere, const F32 *vertexData, U32 vDataCount);
    void BSphereFromBSphereAndPoint(BSphere &bsphere, Math::Vector3D<Real> &p);
    void EigenSphere(BSphere &bsphere, const F32 *vertexData, U32 vDataCount);
    void Grow(BSphere &bsphere0, const BSphere &bsphere1);
}

#endif
