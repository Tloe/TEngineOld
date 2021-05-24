#include <TEContactSet.h>
#include <TEHelpers.h>
#include <TEIntersectionConfig.h>
#include <TEObb.h>
#include <TEObbObbCollider.h>
#include <TEVector3D.h>

Real TE::Intersection::ObbObbCollider::s_contactTime;
Real TE::Intersection::ObbObbCollider::s_minAxisPenetrationDepth;
TE::Math::Vector3D<Real> TE::Intersection::ObbObbCollider::s_contactNormal;

bool TE::Intersection::ObbObbCollider::Collide(const Obb &obb0,
                                               const Obb &obb1,
                                               Real dt,
                                               bool coarse,
                                               bool symetric,
                                               const Math::Vector3D<Real> *pos0 /*= NULL*/,
                                               const Math::Vector3D<Real> *pos1 /*= NULL*/,
                                               const Math::Vector3D<Real> *vel0 /*= NULL*/,
                                               const Math::Vector3D<Real> *vel1 /*= NULL*/,
                                               const Math::Vector3D<Real> *angvel0 /*= NULL*/,
                                               const Math::Vector3D<Real> *angvel1 /*= NULL*/,
                                               ContactSet *contacts) {
    // If coarse just do a quick static check.
    if (coarse)
        return StaticCheck(obb0, obb1);

    // TE::Math::Vector3D<Real> rotAxis0 = *angvel0;
    // physObj0->m_orientation.GetAxis(rotAxis0);
    // rotAxis0.Normalize();
    // TE::Math::Vector3D<Real> rotAxis1 = *angvel1;
    // physObj1->m_orientation.GetAxis(rotAxis1);
    // rotAxis1.Normalize();

    //!!! This should be tested to find a lower value that works well!!!
    // Or use a set step size and calculate the numSteps from that
    static I32 numSteps = 100;

    // The time step for the integration.
    F32 stepsize        = dt / numSteps;

    // Initialize subinterval boxes.
    Obb subObb0         = obb0;
    Obb subObb1         = obb1;

    // integrate the differential equations using Euler's method.
    for (I32 istep = 1; istep <= numSteps; ++istep) {
        F32 subTime                           = stepsize * istep;

        // Compute box velocities and test boxes for intersection.
        //!!! physObj0->m_position is the rotCenter here, if center of mass is used later this needs
        //! to be changed!
        // TE::Math::Vector3D<Real> newpos0 = *pos0 + subTime * (*vel0);
        // TE::Math::Vector3D<Real> newpos1 = *pos1 + subTime * (*vel1);
        // TE::Math::Vector3D<Real> diff0 = subObb0.m_center - newpos0;
        // TE::Math::Vector3D<Real> diff1 = subObb1.m_center - newpos1;

        TE::Math::Vector3D<Real> subVelocity0 = stepsize * (*vel0); // + rotAxis0.Cross(diff0));
        TE::Math::Vector3D<Real> subVelocity1 = stepsize * (*vel1); // + rotAxis1.Cross(diff1));

        if (DynamicCheck(subObb0, subObb1, stepsize, subVelocity0, subVelocity1)) {
            // std::cout << "Dynamic check found contact. Deriving data...." << std::endl;
            if (DeriveContacts(obb0, obb1, subTime, *vel0, *vel1, contacts))
                return true;
            else {
                // std::cout << "...could not derive contact data" << std::endl;
                return false;
            }
        }

        // Update the box centers.
        subObb0.m_center = subObb0.m_center + subVelocity0;
        subObb1.m_center = subObb1.m_center + subVelocity1;

        // Update the box axes.
        for (unsigned i = 0; i < 3; ++i) {
            subObb0.m_axes[i] =
                subObb0.m_axes[i]; // + stepsize*rotAxis0.Cross(subObbs[0].m_axes[i]);
            subObb1.m_axes[i] =
                subObb1.m_axes[i]; //+ stepsize*rotAxis1.Cross(subObbs[1].m_axes[i]);
        }

        // Use Gram-Schmidt to orthonormalize the updated axes. If
        // T/N is small and N is small, this expensive call can be removed,
        // assuming the updated axes are nearly orthonormal
        Orthonormalize(subObb0.m_axes[0], subObb0.m_axes[1], subObb0.m_axes[2]);
        Orthonormalize(subObb1.m_axes[0], subObb1.m_axes[1], subObb1.m_axes[2]);
    }

    return false;
}

bool TE::Intersection::ObbObbCollider::StaticCheck(const Obb &obb0, const Obb &obb1) {
    // Cutoff for cosine of angles between box axes.  This is used to catch
    // the cases when at least one pair of axes are parallel.  If this
    // happens, there is no need to test for separation along the
    // Cross(A[i],B[j]) directions.
    const F32 cutoff        = Math::Base<Real>::REAL_ONE - TE::Math::Base<Real>::EPSILON;
    bool existsParallelPair = false;
    I32 i;

    // Convenience variables.
    const TE::Math::Vector3D<Real> *A = obb0.m_axes;
    const TE::Math::Vector3D<Real> *B = obb1.m_axes;
    const TE::Math::Vector3D<Real> EA = obb0.m_extents;
    const TE::Math::Vector3D<Real> EB = obb1.m_extents;

    // Compute difference of box centers, D = C1-C0.
    TE::Math::Vector3D<Real> D        = obb1.m_center - obb0.m_center;

    F32 C[3][3];    // matrix C = A^T B, c_{ij} = Dot(A_i,B_j)
    F32 AbsC[3][3]; // |c_{ij}|
    F32 AD[3];      // Dot(A_i,D)
    F32 r0, r1, r;  // interval radii and distance between centers
    F32 r01;        // = R0 + R1

    // axis C0+t*A0
    for (i = 0; i < 3; ++i) {
        C[0][i]    = Dot(A[0], B[i]);
        AbsC[0][i] = Math::Base<Real>::Abs(C[0][i]);
        if (AbsC[0][i] > cutoff) {
            existsParallelPair = true;
        }
    }
    AD[0] = Dot(A[0], D);
    r     = Math::Base<Real>::Abs(AD[0]);
    r1    = EB[0] * AbsC[0][0] + EB[1] * AbsC[0][1] + EB[2] * AbsC[0][2];
    r01   = EA[0] + r1;
    if (r > r01) {
        return false;
    }

    // axis C0+t*A1
    for (i = 0; i < 3; ++i) {
        C[1][i]    = Dot(A[1], B[i]);
        AbsC[1][i] = Math::Base<Real>::Abs(C[1][i]);
        if (AbsC[1][i] > cutoff) {
            existsParallelPair = true;
        }
    }
    AD[1] = Dot(A[1], D);
    r     = Math::Base<Real>::Abs(AD[1]);
    r1    = EB[0] * AbsC[1][0] + EB[1] * AbsC[1][1] + EB[2] * AbsC[1][2];
    r01   = EA[1] + r1;
    if (r > r01) {
        return false;
    }

    // axis C0+t*A2
    for (i = 0; i < 3; ++i) {
        C[2][i]    = Dot(A[2], B[i]);
        AbsC[2][i] = Math::Base<Real>::Abs(C[2][i]);
        if (AbsC[2][i] > cutoff) {
            existsParallelPair = true;
        }
    }
    AD[2] = Dot(A[2], D);
    r     = Math::Base<Real>::Abs(AD[2]);
    r1    = EB[0] * AbsC[2][0] + EB[1] * AbsC[2][1] + EB[2] * AbsC[2][2];
    r01   = EA[2] + r1;
    if (r > r01) {
        return false;
    }

    // axis C0+t*B0
    r   = Math::Base<Real>::Abs(Dot(B[0], D));
    r0  = EA[0] * AbsC[0][0] + EA[1] * AbsC[1][0] + EA[2] * AbsC[2][0];
    r01 = r0 + EB[0];
    if (r > r01) {
        return false;
    }

    // axis C0+t*B1
    r   = Math::Base<Real>::Abs(Dot(B[1], D));
    r0  = EA[0] * AbsC[0][1] + EA[1] * AbsC[1][1] + EA[2] * AbsC[2][1];
    r01 = r0 + EB[1];
    if (r > r01) {
        return false;
    }

    // axis C0+t*B2
    r   = Math::Base<Real>::Abs(Dot(B[2], D));
    r0  = EA[0] * AbsC[0][2] + EA[1] * AbsC[1][2] + EA[2] * AbsC[2][2];
    r01 = r0 + EB[2];
    if (r > r01) {
        return false;
    }

    // At least one pair of box axes was parallel, so the separation is
    // effectively in 2D where checking the "edge" normals is sufficient for
    // the separation of the boxes.
    if (existsParallelPair) {
        return true;
    }

    // axis C0+t*A0xB0
    r   = Math::Base<Real>::Abs(AD[2] * C[1][0] - AD[1] * C[2][0]);
    r0  = EA[1] * AbsC[2][0] + EA[2] * AbsC[1][0];
    r1  = EB[1] * AbsC[0][2] + EB[2] * AbsC[0][1];
    r01 = r0 + r1;
    if (r > r01) {
        return false;
    }

    // axis C0+t*A0xB1
    r   = Math::Base<Real>::Abs(AD[2] * C[1][1] - AD[1] * C[2][1]);
    r0  = EA[1] * AbsC[2][1] + EA[2] * AbsC[1][1];
    r1  = EB[0] * AbsC[0][2] + EB[2] * AbsC[0][0];
    r01 = r0 + r1;
    if (r > r01) {
        return false;
    }

    // axis C0+t*A0xB2
    r   = Math::Base<Real>::Abs(AD[2] * C[1][2] - AD[1] * C[2][2]);
    r0  = EA[1] * AbsC[2][2] + EA[2] * AbsC[1][2];
    r1  = EB[0] * AbsC[0][1] + EB[1] * AbsC[0][0];
    r01 = r0 + r1;
    if (r > r01) {
        return false;
    }

    // axis C0+t*A1xB0
    r   = Math::Base<Real>::Abs(AD[0] * C[2][0] - AD[2] * C[0][0]);
    r0  = EA[0] * AbsC[2][0] + EA[2] * AbsC[0][0];
    r1  = EB[1] * AbsC[1][2] + EB[2] * AbsC[1][1];
    r01 = r0 + r1;
    if (r > r01) {
        return false;
    }

    // axis C0+t*A1xB1
    r   = Math::Base<Real>::Abs(AD[0] * C[2][1] - AD[2] * C[0][1]);
    r0  = EA[0] * AbsC[2][1] + EA[2] * AbsC[0][1];
    r1  = EB[0] * AbsC[1][2] + EB[2] * AbsC[1][0];
    r01 = r0 + r1;
    if (r > r01) {
        return false;
    }

    // axis C0+t*A1xB2
    r   = Math::Base<Real>::Abs(AD[0] * C[2][2] - AD[2] * C[0][2]);
    r0  = EA[0] * AbsC[2][2] + EA[2] * AbsC[0][2];
    r1  = EB[0] * AbsC[1][1] + EB[1] * AbsC[1][0];
    r01 = r0 + r1;
    if (r > r01) {
        return false;
    }

    // axis C0+t*A2xB0
    r   = Math::Base<Real>::Abs(AD[1] * C[0][0] - AD[0] * C[1][0]);
    r0  = EA[0] * AbsC[1][0] + EA[1] * AbsC[0][0];
    r1  = EB[1] * AbsC[2][2] + EB[2] * AbsC[2][1];
    r01 = r0 + r1;
    if (r > r01) {
        return false;
    }

    // axis C0+t*A2xB1
    r   = Math::Base<Real>::Abs(AD[1] * C[0][1] - AD[0] * C[1][1]);
    r0  = EA[0] * AbsC[1][1] + EA[1] * AbsC[0][1];
    r1  = EB[0] * AbsC[2][2] + EB[2] * AbsC[2][0];
    r01 = r0 + r1;
    if (r > r01) {
        return false;
    }

    // axis C0+t*A2xB2
    r   = Math::Base<Real>::Abs(AD[1] * C[0][2] - AD[0] * C[1][2]);
    r0  = EA[0] * AbsC[1][2] + EA[1] * AbsC[0][2];
    r1  = EB[0] * AbsC[2][1] + EB[1] * AbsC[2][0];
    r01 = r0 + r1;
    if (r > r01) {
        return false;
    }

    return true;
}

bool TE::Intersection::ObbObbCollider::DynamicCheck(const Obb &obb0,
                                                    const Obb &obb1,
                                                    F32 tmax,
                                                    TE::Math::Vector3D<Real> velocity0,
                                                    TE::Math::Vector3D<Real> velocity1) {
    if (velocity0 == velocity1) {
        s_contactTime = Math::Base<Real>::REAL_ZERO;
        return StaticCheck(obb0, obb1);
    }

    // Cutoff for cosine of angles between box axes.  This is used to catch
    // the cases when at least one pair of axes are parallel.  If this
    // happens, there is no need to include the cross-product axes for
    // separation.
    const F32 cutoff                  = Math::Base<Real>::REAL_ONE - TE::Math::Base<Real>::EPSILON;
    bool existsParallelPair           = false;

    // convenience variables
    const TE::Math::Vector3D<Real> *A = obb0.m_axes;
    const TE::Math::Vector3D<Real> *B = obb1.m_axes;
    const TE::Math::Vector3D<Real> EA = obb0.m_extents;
    const TE::Math::Vector3D<Real> EB = obb1.m_extents;
    TE::Math::Vector3D<Real> D        = obb1.m_center - obb0.m_center;
    TE::Math::Vector3D<Real> W        = velocity1 - velocity0;
    F32 C[3][3];    // matrix C = A^T B, c_{ij} = Dot(A_i,B_j)
    F32 AbsC[3][3]; // |c_{ij}|
    F32 AD[3];      // Dot(A_i,D)
    F32 AW[3];      // Dot(A_i,W)
    F32 min0, max0, min1, max1, center, radius, speed;
    unsigned i, j;

    // m_contactTime = Math::Base<Real>::REAL_ZERO;
    F32 tlast = Math::Base<F32>::MAX_REAL;

    // axes C0+t*A[i]
    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            C[i][j]    = Dot(A[i], B[j]);
            AbsC[i][j] = Math::Base<Real>::Abs(C[i][j]);
            if (AbsC[i][j] > cutoff)
                existsParallelPair = true;
        }
        AD[i]  = Dot(A[i], D);
        AW[i]  = Dot(A[i], W);
        min0   = -EA[i];
        max0   = +EA[i];
        radius = EB[0] * AbsC[i][0] + EB[1] * AbsC[i][1] + EB[2] * AbsC[i][2];
        min1   = AD[i] - radius;
        max1   = AD[i] + radius;
        speed  = AW[i];
        if (IsSeparated(min0, max0, min1, max1, speed, tmax, tlast))
            return false;
    }

    // axes C0+t*B[i]
    for (i = 0; i < 3; ++i) {
        radius = EA[0] * AbsC[0][i] + EA[1] * AbsC[1][i] + EA[2] * AbsC[2][i];
        min0   = -radius;
        max0   = +radius;
        center = Dot(B[i], D);
        min1   = center - EB[i];
        max1   = center + EB[i];
        speed  = Dot(W, B[i]);
        if (IsSeparated(min0, max0, min1, max1, speed, tmax, tlast))
            return false;
    }

    // At least one pair of box axes was parallel, so the separation is
    // effectively in 2D where checking the "edge" normals is sufficient for
    // the separation of the boxes.
    if (existsParallelPair)
        return true;

    // axis C0+t*A0xB0
    radius = EA[1] * AbsC[2][0] + EA[2] * AbsC[1][0];
    min0   = -radius;
    max0   = +radius;
    center = AD[2] * C[1][0] - AD[1] * C[2][0];
    radius = EB[1] * AbsC[0][2] + EB[2] * AbsC[0][1];
    min1   = center - radius;
    max1   = center + radius;
    speed  = AW[2] * C[1][0] - AW[1] * C[2][0];
    if (IsSeparated(min0, max0, min1, max1, speed, tmax, tlast))
        return false;

    // axis C0+t*A0xB1
    radius = EA[1] * AbsC[2][1] + EA[2] * AbsC[1][1];
    min0   = -radius;
    max0   = +radius;
    center = AD[2] * C[1][1] - AD[1] * C[2][1];
    radius = EB[0] * AbsC[0][2] + EB[2] * AbsC[0][0];
    min1   = center - radius;
    max1   = center + radius;
    speed  = AW[2] * C[1][1] - AW[1] * C[2][1];
    if (IsSeparated(min0, max0, min1, max1, speed, tmax, tlast))
        return false;

    // axis C0+t*A0xB2
    radius = EA[1] * AbsC[2][2] + EA[2] * AbsC[1][2];
    min0   = -radius;
    max0   = +radius;
    center = AD[2] * C[1][2] - AD[1] * C[2][2];
    radius = EB[0] * AbsC[0][1] + EB[1] * AbsC[0][0];
    min1   = center - radius;
    max1   = center + radius;
    speed  = AW[2] * C[1][2] - AW[1] * C[2][2];
    if (IsSeparated(min0, max0, min1, max1, speed, tmax, tlast))
        return false;

    // axis C0+t*A1xB0
    radius = EA[0] * AbsC[2][0] + EA[2] * AbsC[0][0];
    min0   = -radius;
    max0   = +radius;
    center = AD[0] * C[2][0] - AD[2] * C[0][0];
    radius = EB[1] * AbsC[1][2] + EB[2] * AbsC[1][1];
    min1   = center - radius;
    max1   = center + radius;
    speed  = AW[0] * C[2][0] - AW[2] * C[0][0];
    if (IsSeparated(min0, max0, min1, max1, speed, tmax, tlast))
        return false;

    // axis C0+t*A1xB1
    radius = EA[0] * AbsC[2][1] + EA[2] * AbsC[0][1];
    min0   = -radius;
    max0   = +radius;
    center = AD[0] * C[2][1] - AD[2] * C[0][1];
    radius = EB[0] * AbsC[1][2] + EB[2] * AbsC[1][0];
    min1   = center - radius;
    max1   = center + radius;
    speed  = AW[0] * C[2][1] - AW[2] * C[0][1];
    if (IsSeparated(min0, max0, min1, max1, speed, tmax, tlast))
        return false;

    // axis C0+t*A1xB2
    radius = EA[0] * AbsC[2][2] + EA[2] * AbsC[0][2];
    min0   = -radius;
    max0   = +radius;
    center = AD[0] * C[2][2] - AD[2] * C[0][2];
    radius = EB[0] * AbsC[1][1] + EB[1] * AbsC[1][0];
    min1   = center - radius;
    max1   = center + radius;
    speed  = AW[0] * C[2][2] - AW[2] * C[0][2];
    if (IsSeparated(min0, max0, min1, max1, speed, tmax, tlast))
        return false;

    // axis C0+t*A2xB0
    radius = EA[0] * AbsC[1][0] + EA[1] * AbsC[0][0];
    min0   = -radius;
    max0   = +radius;
    center = AD[1] * C[0][0] - AD[0] * C[1][0];
    radius = EB[1] * AbsC[2][2] + EB[2] * AbsC[2][1];
    min1   = center - radius;
    max1   = center + radius;
    speed  = AW[1] * C[0][0] - AW[0] * C[1][0];
    if (IsSeparated(min0, max0, min1, max1, speed, tmax, tlast))
        return false;

    // axis C0+t*A2xB1
    radius = EA[0] * AbsC[1][1] + EA[1] * AbsC[0][1];
    min0   = -radius;
    max0   = +radius;
    center = AD[1] * C[0][1] - AD[0] * C[1][1];
    radius = EB[0] * AbsC[2][2] + EB[2] * AbsC[2][0];
    min1   = center - radius;
    max1   = center + radius;
    speed  = AW[1] * C[0][1] - AW[0] * C[1][1];
    if (IsSeparated(min0, max0, min1, max1, speed, tmax, tlast))
        return false;

    // axis C0+t*A2xB2
    radius = EA[0] * AbsC[1][2] + EA[1] * AbsC[0][2];
    min0   = -radius;
    max0   = +radius;
    center = AD[1] * C[0][2] - AD[0] * C[1][2];
    radius = EB[0] * AbsC[2][1] + EB[1] * AbsC[2][0];
    min1   = center - radius;
    max1   = center + radius;
    speed  = AW[1] * C[0][2] - AW[0] * C[1][2];
    if (IsSeparated(min0, max0, min1, max1, speed, tmax, tlast))
        return false;

    return true;
}

bool TE::Intersection::ObbObbCollider::DeriveContacts(const Obb &obb0,
                                                      const Obb &obb1,
                                                      F32 tmax,
                                                      const TE::Math::Vector3D<Real> &velocity0,
                                                      const TE::Math::Vector3D<Real> &velocity1,
                                                      ContactSet *contacts) {
    s_contactTime                        = Math::Base<Real>::REAL_ZERO;
    F32 tlast                            = Math::Base<F32>::MAX_REAL;

    // Relative velocity of box1 relative to box0.
    TE::Math::Vector3D<Real> relVelocity = velocity1 - velocity0;

    I32 i0, i1;
    I32 side = intersectConfig::NONE;
    intersectConfig box0Cfg, box1Cfg;
    TE::Math::Vector3D<Real> axis;

    // box 0 normals
    for (i0 = 0; i0 < 3; ++i0) {
        axis = obb0.m_axes[i0];
        if (!FindintersectionOnAxis(obb0, obb1, axis, relVelocity, tmax, s_contactTime, tlast, side,
                                    box0Cfg, box1Cfg))
            return false;
    }

    // box 1 normals
    for (i1 = 0; i1 < 3; ++i1) {
        axis = obb1.m_axes[i1];
        if (!FindintersectionOnAxis(obb0, obb1, axis, relVelocity, tmax, s_contactTime, tlast, side,
                                    box0Cfg, box1Cfg))
            return false;
    }

    // box 0 edges cross box 1 edges
    for (i0 = 0; i0 < 3; ++i0) {
        for (i1 = 0; i1 < 3; ++i1) {
            axis = Cross(obb0.m_axes[i0], obb1.m_axes[i1]);

            // Since all axes are unit length (assumed), then can just compare
            // against a constant (not relative) epsilon.
            if (MagnitudeSqr(axis) <= TE::Math::Base<Real>::EPSILON) {
                // Axis i0 and i1 are parallel.  If any two axes are parallel,
                // then the only comparisons that needed are between the faces
                // themselves.  At this time the faces have already been
                // tested, and without separation, so all further separation
                // tests will show only overlaps.
                FindContactSet(obb0, obb1, velocity0, velocity1, side, box0Cfg, box1Cfg,
                               s_contactTime);
                return true;
            }

            if (!FindintersectionOnAxis(obb0, obb1, axis, relVelocity, tmax, s_contactTime, tlast,
                                        side, box0Cfg, box1Cfg))
                return false;
        }
    }

    // velocity cross box 0 edges
    for (i0 = 0; i0 < 3; ++i0) {
        axis = Cross(relVelocity, obb0.m_axes[i0]);
        if (!FindintersectionOnAxis(obb0, obb1, axis, relVelocity, tmax, s_contactTime, tlast, side,
                                    box0Cfg, box1Cfg))
            return false;
    }

    // velocity cross box 1 edges
    for (i1 = 0; i1 < 3; ++i1) {
        axis = Cross(relVelocity, obb1.m_axes[i1]);
        if (!FindintersectionOnAxis(obb0, obb1, axis, relVelocity, tmax, s_contactTime, tlast, side,
                                    box0Cfg, box1Cfg))
            return false;
    }

    if (s_contactTime <= Math::Base<Real>::REAL_ZERO || side == intersectConfig::NONE)
        return false;

    FindContactSet(obb0, obb1, velocity0, velocity1, side, box0Cfg, box1Cfg, s_contactTime);

    return true;
}

bool TE::Intersection::ObbObbCollider::IsSeparated(F32 min0,
                                                   F32 max0,
                                                   F32 min1,
                                                   F32 max1,
                                                   F32 speed,
                                                   F32 tmax,
                                                   F32 &tlast) {
    s_minAxisPenetrationDepth = Math::Base<Real>::MAX_REAL;

    F32 invSpeed, t;

    if (max1 < min0) // box1 initially on left of box0
    {
        if (speed <= Math::Base<Real>::REAL_ZERO)
            // The projection intervals are moving apart.
            return true;

        invSpeed = Math::Base<Real>::REAL_ONE / speed;

        t        = (min0 - max1) * invSpeed;

        if (t > s_contactTime)
            s_contactTime = t;

        if (s_contactTime > tmax)
            // intervals do not intersect during the specified time.
            return true;

        t = (max0 - min1) * invSpeed;

        if (t < tlast)
            tlast = t;

        if (s_contactTime > tlast)
            // Physically inconsistent times--the objects cannot intersect.
            return true;

        F32 currPenetration = max1 - min0;
        if (currPenetration < s_minAxisPenetrationDepth)
            s_minAxisPenetrationDepth = currPenetration;
    } else if (max0 < min1) // box1 initially on right of box0
    {
        if (speed >= Math::Base<Real>::REAL_ZERO)
            // The projection intervals are moving apart.
            return true;

        invSpeed = Math::Base<Real>::REAL_ONE / speed;

        t        = (max0 - min1) * invSpeed;

        if (t > s_contactTime)
            s_contactTime = t;

        if (s_contactTime > tmax)
            // intervals do not intersect during the specified time.
            return true;

        t = (min0 - max1) * invSpeed;

        if (t < tlast)
            tlast = t;

        if (s_contactTime > tlast)
            // Physically inconsistent times--the objects cannot intersect.
            return true;

        F32 currPenetration = max0 - min1;
        if (currPenetration < s_minAxisPenetrationDepth)
            s_minAxisPenetrationDepth = currPenetration;
    } else // box0 and box1 initially overlap
    {
        if (speed > Math::Base<Real>::REAL_ZERO) {
            t = (max0 - min1) / speed;

            if (t < tlast)
                tlast = t;

            if (s_contactTime > tlast)
                // Physically inconsistent times--the objects cannot intersect.
                return true;

            F32 currPenetration = max1 - min0;
            if (currPenetration < s_minAxisPenetrationDepth)
                s_minAxisPenetrationDepth = currPenetration;
        } else if (speed < Math::Base<Real>::REAL_ZERO) {
            t = (min0 - max1) / speed;

            if (t < tlast)
                tlast = t;

            if (s_contactTime > tlast)
                // Physically inconsistent times--the objects cannot intersect.
                return true;

            F32 currPenetration = max0 - min1;
            if (currPenetration < s_minAxisPenetrationDepth)
                s_minAxisPenetrationDepth = currPenetration;
        }
    }

    return false;
}

bool TE::Intersection::ObbObbCollider::FindintersectionOnAxis(
    const Obb &obb0,
    const Obb &obb1,
    const TE::Math::Vector3D<Real> &axis,
    const TE::Math::Vector3D<Real> &velocity,
    F32 tmax,
    F32 &tfirst,
    F32 &tlast,
    I32 &side,
    intersectConfig &box0CfgFinal,
    intersectConfig &box1CfgFinal) {
    intersectConfig box0CfgStart;
    box0CfgStart.setConfiguration(axis, obb0);

    intersectConfig box1CfgStart;
    box1CfgStart.setConfiguration(axis, obb1);

    // Constant velocity separating axis test.  The configurations cfg0Start
    // and cfg1Start are the current potential configurations for contact,
    // and cfg0Final and cfg1Final are improved configurations.

    F32 t;
    F32 speed = Dot(axis, velocity);

    if (box1CfgStart.m_max < box0CfgStart.m_min) // object1 left of object0
    {
        if (speed <= Math::Base<Real>::REAL_ZERO) // object1 moving away from object0
            return false;

        // find first time of contact on this axis
        t = (box0CfgStart.m_min - box1CfgStart.m_max) / speed;

        // If this is the new maximum first time of contact, set side and
        // configuration.
        if (t > tfirst) {
            tfirst          = t;
            side            = intersectConfig::LEFT;
            box0CfgFinal    = box0CfgStart;
            box1CfgFinal    = box1CfgStart;
            s_contactNormal = axis;
        }

        // quick out: intersection after desired interval
        if (tfirst > tmax)
            return false;

        // find last time of contact on this axis
        t = (box0CfgStart.m_max - box1CfgStart.m_min) / speed;
        if (t < tlast)
            tlast = t;

        // quick out: intersection before desired interval
        if (tfirst > tlast)
            return false;
    } else if (box0CfgStart.m_max < box1CfgStart.m_min) // obj1 right of obj0
    {
        if (speed >= Math::Base<Real>::REAL_ZERO) // object1 moving away from object0
            return false;

        // find first time of contact on this axis
        t = (box0CfgStart.m_max - box1CfgStart.m_min) / speed;

        // If this is the new maximum first time of contact,  set side and
        // configuration.
        if (t > tfirst) {
            tfirst          = t;
            side            = intersectConfig::RIGHT;
            box0CfgFinal    = box0CfgStart;
            box1CfgFinal    = box1CfgStart;
            s_contactNormal = axis;
        }

        // quick out: intersection after desired interval
        if (tfirst > tmax)
            return false;

        // find last time of contact on this axis
        t = (box0CfgStart.m_min - box1CfgStart.m_max) / speed;
        if (t < tlast)
            tlast = t;

        // quick out: intersection before desired interval
        if (tfirst > tlast)
            return false;
    } else // object1 and object0 on overlapping interval
    {
        if (speed > Math::Base<Real>::REAL_ZERO) {
            // find last time of contact on this axis
            t = (box0CfgStart.m_max - box1CfgStart.m_min) / speed;
            if (t < tlast) {
                tlast           = t;
                s_contactNormal = axis;
            }

            // quick out: intersection before desired interval
            if (tfirst > tlast)
                return false;
        } else if (speed < Math::Base<Real>::REAL_ZERO) {
            // find last time of contact on this axis
            t = (box0CfgStart.m_min - box1CfgStart.m_max) / speed;
            if (t < tlast) {
                tlast           = t;
                s_contactNormal = axis;
            }

            // quick out: intersection before desired interval
            if (tfirst > tlast)
                return false;
        }
    }
    return true;
}

void TE::Intersection::ObbObbCollider::FindContactSet(const Obb &obb0,
                                                      const Obb &obb1,
                                                      const TE::Math::Vector3D<Real> &velocity0,
                                                      const TE::Math::Vector3D<Real> &velocity1,
                                                      I32 side,
                                                      const intersectConfig &box0Cfg,
                                                      const intersectConfig &box1Cfg,
                                                      F32 tfirst,
                                                      ContactSet *contacts) {
    TE::Math::Vector3D<Real> pts[8];
    I32 numPts;

    // Move the boxes to their new positions.
    TE::Intersection::Obb box0Final, box1Final;
    box0Final          = obb0;
    box1Final          = obb1;
    box0Final.m_center = obb0.m_center + tfirst * velocity0;
    box1Final.m_center = obb1.m_center + tfirst * velocity1;

    const I32 *b0Index = box0Cfg.m_index;
    const I32 *b1Index = box1Cfg.m_index;

    std::cout << "b0: ";
    for (I32 i = 0; i < 8; i++) {
        std::cout << b0Index[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "b1: ";
    for (I32 i = 0; i < 8; i++) {
        std::cout << b1Index[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Contact: ";

    if (side == TE::Intersection::intersectConfig::LEFT) {
        // box1 on left of box0
        if (box0Cfg.m_map == TE::Intersection::intersectConfig::m1_1) {
            // box0point-box1face
            numPts = 1;
            pts[0] = GetPointFromIndex(box0Final, b0Index[0]);
            std::cout << "0 - point-face collision!" << std::endl;
        } else if (box1Cfg.m_map == intersectConfig::m1_1) {
            // box0face-box1point
            numPts = 1;
            pts[0] = GetPointFromIndex(box1Final, b1Index[7]);
            std::cout << "1 - face-point collision!" << std::endl;
        } else if (box0Cfg.m_map == intersectConfig::m2_2) {
            if (box1Cfg.m_map == intersectConfig::m2_2) {
                // box0edge-box1edge intersection
                TE::Math::Vector3D<Real> edge0[2], edge1[2];
                edge0[0] = GetPointFromIndex(box0Final, b0Index[0]);
                edge0[1] = GetPointFromIndex(box0Final, b0Index[1]);
                edge1[0] = GetPointFromIndex(box1Final, b1Index[6]);
                edge1[1] = GetPointFromIndex(box1Final, b1Index[7]);
                TE::Math::Helpers<Real>::segmentSegment(edge0, edge1, numPts, pts);
                std::cout << "2 - edge-edge collision!" << std::endl;
            } else // box1Cfg.m_map == m44
            {
                // box0edge-box1face intersection
                TE::Math::Vector3D<Real> edge0[2], face1[4];
                edge0[0] = GetPointFromIndex(box0Final, b0Index[0]);
                edge0[1] = GetPointFromIndex(box0Final, b0Index[1]);
                face1[0] = GetPointFromIndex(box1Final, b1Index[4]);
                face1[1] = GetPointFromIndex(box1Final, b1Index[5]);
                face1[2] = GetPointFromIndex(box1Final, b1Index[6]);
                face1[3] = GetPointFromIndex(box1Final, b1Index[7]);
                TE::Math::Helpers<Real>::coplanarSegmentRectangle(edge0, face1, numPts, pts);
                std::cout << "3 - edge-face collision!" << std::endl;
            }
        } else // box0Cfg.m_map == m44
        {
            if (box1Cfg.m_map == intersectConfig::m2_2) {
                // box0face-box1edge intersection
                TE::Math::Vector3D<Real> face0[4], edge1[2];
                face0[0] = GetPointFromIndex(box0Final, b0Index[0]);
                face0[1] = GetPointFromIndex(box0Final, b0Index[1]);
                face0[2] = GetPointFromIndex(box0Final, b0Index[2]);
                face0[3] = GetPointFromIndex(box0Final, b0Index[3]);
                edge1[0] = GetPointFromIndex(box1Final, b1Index[6]);
                edge1[1] = GetPointFromIndex(box1Final, b1Index[7]);
                TE::Math::Helpers<Real>::coplanarSegmentRectangle(edge1, face0, numPts, pts);
                std::cout << "4 - face-edge collision!" << std::endl;
            } else {
                // box0face-box1face intersection
                TE::Math::Vector3D<Real> face0[4], face1[4];
                face0[0] = GetPointFromIndex(box0Final, b0Index[0]);
                face0[1] = GetPointFromIndex(box0Final, b0Index[1]);
                face0[2] = GetPointFromIndex(box0Final, b0Index[2]);
                face0[3] = GetPointFromIndex(box0Final, b0Index[3]);
                face1[0] = GetPointFromIndex(box1Final, b1Index[4]);
                face1[1] = GetPointFromIndex(box1Final, b1Index[5]);
                face1[2] = GetPointFromIndex(box1Final, b1Index[6]);
                face1[3] = GetPointFromIndex(box1Final, b1Index[7]);
                TE::Math::Helpers<Real>::coplanarRectangleRectangle(face0, face1, numPts, pts);
                std::cout << "5 - face-face collision!" << std::endl;
            }
        }
    } else // side == RIGHT
    {
        // box1 on right of box0
        if (box0Cfg.m_map == intersectConfig::m1_1) {
            // box0point-box1face
            numPts = 1;
            pts[0] = GetPointFromIndex(box0Final, b0Index[7]);
            std::cout << "6 - point-face collision!" << std::endl;
        } else if (box1Cfg.m_map == intersectConfig::m1_1) {
            // box0face-box1point
            numPts = 1;
            pts[0] = GetPointFromIndex(box1Final, b1Index[0]);
            std::cout << "7 - face-point collision!" << std::endl;
        } else if (box0Cfg.m_map == intersectConfig::m2_2) {
            if (box1Cfg.m_map == intersectConfig::m2_2) {
                // box0edge-box1edge intersection
                TE::Math::Vector3D<Real> edge0[2], edge1[2];
                edge0[0] = GetPointFromIndex(box0Final, b0Index[6]);
                edge0[1] = GetPointFromIndex(box0Final, b0Index[7]);
                edge1[0] = GetPointFromIndex(box1Final, b1Index[0]);
                edge1[1] = GetPointFromIndex(box1Final, b1Index[1]);
                TE::Math::Helpers<Real>::segmentSegment(edge0, edge1, numPts, pts);
                std::cout << "8 - edge-edge collision!" << std::endl;
            } else // box1Cfg.m_map == m44
            {
                // box0edge-box1face intersection
                TE::Math::Vector3D<Real> edge0[2], face1[4];
                edge0[0] = GetPointFromIndex(box0Final, b0Index[6]);
                edge0[1] = GetPointFromIndex(box0Final, b0Index[7]);
                face1[0] = GetPointFromIndex(box1Final, b1Index[0]);
                face1[1] = GetPointFromIndex(box1Final, b1Index[1]);
                face1[2] = GetPointFromIndex(box1Final, b1Index[2]);
                face1[3] = GetPointFromIndex(box1Final, b1Index[3]);
                TE::Math::Helpers<Real>::coplanarSegmentRectangle(edge0, face1, numPts, pts);
                std::cout << "9 - edge-face collision!" << std::endl;
            }
        } else // box0Cfg.m_map == m44
        {
            if (box1Cfg.m_map == intersectConfig::m2_2) {
                // box0face-box1edge intersection
                TE::Math::Vector3D<Real> face0[4], edge1[2];
                face0[0] = GetPointFromIndex(box0Final, b0Index[4]);
                face0[1] = GetPointFromIndex(box0Final, b0Index[5]);
                face0[2] = GetPointFromIndex(box0Final, b0Index[6]);
                face0[3] = GetPointFromIndex(box0Final, b0Index[7]);
                edge1[0] = GetPointFromIndex(box1Final, b1Index[0]);
                edge1[1] = GetPointFromIndex(box1Final, b1Index[1]);
                TE::Math::Helpers<Real>::coplanarSegmentRectangle(edge1, face0, numPts, pts);
                std::cout << "10 - face-edge collision!" << std::endl;
            } else // box1Cfg.m_map == m44
            {
                // box0face-box1face intersection
                TE::Math::Vector3D<Real> face0[4], face1[4];
                face0[0] = GetPointFromIndex(box0Final, b0Index[4]);
                face0[1] = GetPointFromIndex(box0Final, b0Index[5]);
                face0[2] = GetPointFromIndex(box0Final, b0Index[6]);
                face0[3] = GetPointFromIndex(box0Final, b0Index[7]);
                face1[0] = GetPointFromIndex(box1Final, b1Index[0]);
                face1[1] = GetPointFromIndex(box1Final, b1Index[1]);
                face1[2] = GetPointFromIndex(box1Final, b1Index[2]);
                face1[3] = GetPointFromIndex(box1Final, b1Index[3]);
                TE::Math::Helpers<Real>::coplanarRectangleRectangle(face0, face1, numPts, pts);
                std::cout << "11 - face-face collision!" << std::endl;
            }
        }
    }

    s_contactNormal.Normalize();
    TE::Math::Vector3D<Real> direction = obb1.m_center - obb0.m_center;
    F32 diff                           = Dot(s_contactNormal, direction);
    if (diff > Math::Base<Real>::REAL_ZERO)
        s_contactNormal = -s_contactNormal;

    std::cout << "normal: " << s_contactNormal << std::endl
              << "Points: " << numPts << std::endl
              << "End" << std::endl
              << std::endl;

    TE::Math::Vector3D<Real> colPt;

    for (I32 i = 0; i < numPts; ++i) {
        contacts->points.push_back(pts[i]);
    }

    contacts->normals.push_back(s_contactNormal);
    contacts->penetrations.push_back(s_minAxisPenetrationDepth);
}
