#include <TEHelpers.h>
#include <TEMathBase.h>
#include <TEMatrix4D.h>
#include <TEObb.h>
#include <TEQuaternion.h>
#include <TEVector3D.h>

TE::Intersection::Obb::Obb(const TE::Math::Vector3D<Real> &center, const TE::Math::Vector3D<Real> axes[], const TE::Math::Vector3D<Real> &extents) {
    m_center  = center;
    m_extents = extents;
    m_axes[0] = axes[0];
    m_axes[1] = axes[1];
    m_axes[2] = axes[2];
}

TE::Intersection::Obb::Obb(const TE::Intersection::Obb &rhs) {
    m_center  = rhs.m_center;
    m_extents = rhs.m_extents;
    m_axes[0] = rhs.m_axes[0];
    m_axes[1] = rhs.m_axes[1];
    m_axes[2] = rhs.m_axes[2];
}

TE::Intersection::Obb &TE::Intersection::Obb::operator=(const TE::Intersection::Obb &rhs) {
    if (this != &rhs) {
        m_center  = rhs.m_center;
        m_extents = rhs.m_extents;
        m_axes[0] = rhs.m_axes[0];
        m_axes[1] = rhs.m_axes[1];
        m_axes[2] = rhs.m_axes[2];
    }
    return *this;
}

void TE::Intersection::Rotate(Obb &obb, Math::Quaternion<Real> &orientation) {
    orientation.Normalize();
    obb.m_axes[0] = Rotate(obb.m_axes[0], orientation);
    obb.m_axes[1] = Rotate(obb.m_axes[1], orientation);
    obb.m_axes[2] = Rotate(obb.m_axes[2], orientation);
}

void TE::Intersection::ObbFromVertexData(Obb &obb, const F32 *vertexData, unsigned vDataCount) {
    // Calc box center
    obb.m_center = TE::Math::Vector3D<Real>(vertexData[0], vertexData[1], vertexData[2]);
    for (unsigned i = 3; i < vDataCount - 2; i += 3) {
        obb.m_center += TE::Math::Vector3D<Real>(vertexData[i + 0], vertexData[i + 1], vertexData[i + 2]);
    }

    F32 invNumPoints = Math::Base<Real>::REAL_ONE / (vDataCount / 3);
    obb.m_center *= invNumPoints;

    // Calc eigen-vectors/values, and store it in the obb
    TE::Math::Matrix4D<Real> m, v;
    TE::Math::Helpers<Real>::covarianceMatrixOfPts(m, vertexData, vDataCount);

    TE::Math::Helpers<Real>::jacobi(m, v);

    for (unsigned i = 0; i < 3; ++i) {
        obb.m_extents[i] = m(i, i);
        for (unsigned j = 0; j < 3; ++j)
            obb.m_axes[i][j] = v(j, i);
    }

    // Let C be the box center and let U0, U1, and U2 be the box axes.  Each
    // input point is of the form X = C + y0*U0 + y1*U1 + y2*U2.  The
    // following code computes min(y0), max(y0), min(y1), max(y1), min(y2),
    // and max(y2).  The box center is then adjusted to be
    //   C' = C + 0.5*(min(y0)+max(y0))*U0 + 0.5*(min(y1)+max(y1))*U1 +
    //        0.5*(min(y2)+max(y2))*U2
    TE::Math::Vector3D<Real> diff = TE::Math::Vector3D<Real>(vertexData[0], vertexData[1], vertexData[2]) - obb.m_center;
    TE::Math::Vector3D<Real> pmin = TE::Math::Vector3D<Real>(Dot(diff, obb.m_axes[0]), Dot(diff, obb.m_axes[1]), Dot(diff, obb.m_axes[2]));
    TE::Math::Vector3D<Real> pmax = pmin;
    for (unsigned i = 3; i < vDataCount - 2; i += 3) {
        diff = TE::Math::Vector3D<Real>(vertexData[i + 0], vertexData[i + 1], vertexData[i + 2]) - obb.m_center;
        for (unsigned j = 0; j < 3; ++j) {
            F32 dot = Dot(diff, obb.m_axes[j]);
            if (dot < pmin[j])
                pmin[j] = dot;
            else if (dot > pmax[j])
                pmax[j] = dot;
        }
    }

    obb.m_center += (0.5f * (pmin[0] + pmax[0])) * obb.m_axes[0] +
                    (0.5f * (pmin[1] + pmax[1])) * obb.m_axes[1] +
                    (0.5f * (pmin[2] + pmax[2])) * obb.m_axes[2];

    obb.m_extents[0] = 0.5f * (pmax[0] - pmin[0]);
    obb.m_extents[1] = 0.5f * (pmax[1] - pmin[1]);
    obb.m_extents[2] = 0.5f * (pmax[2] - pmin[2]);
}

TE::Math::Vector3D<Real> TE::Intersection::FindNearestPointOnObb(const Obb &obb, const Math::Vector3D<Real> &p) {
    TE::Math::Vector3D<Real> retPt;
    TE::Math::Vector3D<Real> d = p - obb.m_center;

    retPt                      = obb.m_center;
    for (I32 i = 0; i < 3; ++i) {
        F32 dist = Dot(d, obb.m_axes[i]);
        if (dist > obb.m_extents[i])
            dist = obb.m_extents[i];
        if (dist < -obb.m_extents[i])
            dist = -obb.m_extents[i];
        retPt += dist * obb.m_axes[i];
    }

    return retPt;
}

TE::Math::Vector3D<Real> TE::Intersection::GetPointFromIndex(const Obb &obb, I32 index) {
    TE::Math::Vector3D<Real> point = obb.m_center;

    if (index & 4)
        point += obb.m_extents[2] * obb.m_axes[2];
    else
        point -= obb.m_extents[2] * obb.m_axes[2];

    if (index & 2)
        point += obb.m_extents[1] * obb.m_axes[1];
    else
        point -= obb.m_extents[1] * obb.m_axes[1];

    if (index & 1)
        point += obb.m_extents[0] * obb.m_axes[0];
    else
        point -= obb.m_extents[0] * obb.m_axes[0];

    return point;
}
