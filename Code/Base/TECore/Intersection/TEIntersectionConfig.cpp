#include <TEIntersectionConfig.h>
#include <TEMathBase.h>
#include <TEObb.h>
#include <TEVector3D.h>

void TE::Intersection::intersectConfig::setConfiguration(const TE::Math::Vector3D<Real> &axis, const Obb &obb) {
    // Description of coordinate ordering scheme for intersectionConfig.m_index.
    //
    // Vertex number (up/down) vs. sign of extent (only matters in mapping back)
    //   012
    // 0 ---
    // 1 +--
    // 2 -+-
    // 3 ++-
    // 4 --+
    // 5 +-+
    // 6 -++
    // 7 +++
    //
    // When it returns an ordering in the intrConfiguration, it is also
    // guarenteed to be in-order (if 4 vertices, then they are guarenteed in
    // an order that will create a box, e.g. 0,1,3,2).
    F32 axes[3] =
        {
            Dot(axis, obb.m_axes[0]),
            Dot(axis, obb.m_axes[1]),
            Dot(axis, obb.m_axes[2])};

    F32 absAxes[3] =
        {
            Math::Base<Real>::Abs(axes[0]),
            Math::Base<Real>::Abs(axes[1]),
            Math::Base<Real>::Abs(axes[2])};

    F32 maxProjectedExtent;

    if (absAxes[0] < TE::Math::Base<Real>::EPSILON) {
        if (absAxes[1] < TE::Math::Base<Real>::EPSILON) {
            // face-face
            m_map              = m44;

            maxProjectedExtent = absAxes[2] * obb.m_extents[2];

            // faces have normals along axis[2]
            if (axes[2] > Math::Base<Real>::REAL_ZERO) {
                m_index[0] = 0;
                m_index[1] = 1;
                m_index[2] = 3;
                m_index[3] = 2;

                m_index[4] = 6;
                m_index[5] = 7;
                m_index[6] = 5;
                m_index[7] = 4;
            } else {
                m_index[0] = 6;
                m_index[1] = 7;
                m_index[2] = 5;
                m_index[3] = 4;

                m_index[4] = 0;
                m_index[5] = 1;
                m_index[6] = 3;
                m_index[7] = 2;
            }
        } else if (absAxes[2] < TE::Math::Base<Real>::EPSILON) {
            // face-face
            m_map              = m44;

            maxProjectedExtent = absAxes[1] * obb.m_extents[1];

            // faces have normals along axis[1]
            if (axes[1] > Math::Base<Real>::REAL_ZERO) {
                m_index[0] = 4;
                m_index[1] = 5;
                m_index[2] = 1;
                m_index[3] = 0;

                m_index[4] = 2;
                m_index[5] = 3;
                m_index[6] = 7;
                m_index[7] = 6;
            } else {
                m_index[0] = 2;
                m_index[1] = 3;
                m_index[2] = 7;
                m_index[3] = 6;

                m_index[4] = 4;
                m_index[5] = 5;
                m_index[6] = 1;
                m_index[7] = 0;
            }
        } else // only axes[0] is equal to 0
        {
            // seg-seg
            m_map              = m2_2;

            maxProjectedExtent = absAxes[1] * obb.m_extents[1] +
                                 absAxes[2] * obb.m_extents[2];

            // axis 0 is perpendicular to axis
            if (axes[1] > Math::Base<Real>::REAL_ZERO) {
                if (axes[2] > Math::Base<Real>::REAL_ZERO) {
                    m_index[0] = 0;
                    m_index[1] = 1;

                    m_index[6] = 6;
                    m_index[7] = 7;
                } else {
                    m_index[0] = 4;
                    m_index[1] = 5;

                    m_index[6] = 2;
                    m_index[7] = 3;
                }
            } else // axes[1] < 0
            {
                if (axes[2] > Math::Base<Real>::REAL_ZERO) {
                    m_index[0] = 2;
                    m_index[1] = 3;

                    m_index[6] = 4;
                    m_index[7] = 5;
                } else {
                    m_index[0] = 6;
                    m_index[1] = 7;

                    m_index[6] = 0;
                    m_index[7] = 1;
                }
            }
        }
    } else if (absAxes[1] < TE::Math::Base<Real>::EPSILON) {
        if (absAxes[2] < TE::Math::Base<Real>::EPSILON) {
            // face-face
            m_map              = m44;

            maxProjectedExtent = absAxes[0] * obb.m_extents[0];

            // faces have normals along axis[0]
            if (axes[0] > Math::Base<Real>::REAL_ZERO) {
                m_index[0] = 0;
                m_index[1] = 2;
                m_index[2] = 6;
                m_index[3] = 4;

                m_index[4] = 5;
                m_index[5] = 7;
                m_index[6] = 3;
                m_index[7] = 1;
            } else {
                m_index[4] = 0;
                m_index[5] = 2;
                m_index[6] = 6;
                m_index[7] = 4;

                m_index[0] = 5;
                m_index[1] = 7;
                m_index[2] = 3;
                m_index[3] = 1;
            }

        } else // only axes[1] is equal to 0
        {
            // seg-seg
            m_map              = m2_2;

            maxProjectedExtent = absAxes[0] * obb.m_extents[0] + absAxes[2] * obb.m_extents[2];

            // axis 1 is perpendicular to axis
            if (axes[0] > Math::Base<Real>::REAL_ZERO) {
                if (axes[2] > Math::Base<Real>::REAL_ZERO) {
                    m_index[0] = 0;
                    m_index[1] = 2;

                    m_index[6] = 5;
                    m_index[7] = 7;
                } else {
                    m_index[0] = 4;
                    m_index[1] = 6;

                    m_index[6] = 1;
                    m_index[7] = 3;
                }
            } else // axes[0] < 0
            {
                if (axes[2] > Math::Base<Real>::REAL_ZERO) {
                    m_index[0] = 1;
                    m_index[1] = 3;

                    m_index[6] = 4;
                    m_index[7] = 6;
                } else {
                    m_index[0] = 5;
                    m_index[1] = 7;

                    m_index[6] = 0;
                    m_index[7] = 2;
                }
            }
        }
    } else if (absAxes[2] < TE::Math::Base<Real>::EPSILON) {
        // only axis2 less than zero
        // seg-seg
        m_map              = m2_2;

        maxProjectedExtent = absAxes[0] * obb.m_extents[0] + absAxes[1] * obb.m_extents[1];

        // axis 2 is perpendicular to axis
        if (axes[0] > Math::Base<Real>::REAL_ZERO) {
            if (axes[1] > Math::Base<Real>::REAL_ZERO) {
                m_index[0] = 0;
                m_index[1] = 4;

                m_index[6] = 3;
                m_index[7] = 7;
            } else {
                m_index[0] = 2;
                m_index[1] = 6;

                m_index[6] = 1;
                m_index[7] = 5;
            }
        } else // axes[0] < 0
        {
            if (axes[1] > Math::Base<Real>::REAL_ZERO) {
                m_index[0] = 1;
                m_index[1] = 5;

                m_index[6] = 2;
                m_index[7] = 6;
            } else {
                m_index[0] = 3;
                m_index[1] = 7;

                m_index[6] = 0;
                m_index[7] = 4;
            }
        }
    }

    else // no axis is equal to zero
    {
        // point-point (unique maximal and minimal vertex)
        m_map              = m1_1;

        maxProjectedExtent = absAxes[0] * obb.m_extents[0] + absAxes[1] * obb.m_extents[1] + absAxes[2] * obb.m_extents[2];

        // only these two vertices matter, the rest are irrelevant
        m_index[0] =
            (axes[0] > Math::Base<Real>::REAL_ZERO ? 0 : 1) +
            (axes[1] > Math::Base<Real>::REAL_ZERO ? 0 : 2) +
            (axes[2] > Math::Base<Real>::REAL_ZERO ? 0 : 4);
        // by ordering the vertices this way, opposite corners add up to 7
        m_index[7] = 7 - m_index[0];
    }

    // Find projections onto line
    F32 origin = Dot(axis, obb.m_center);
    m_min      = origin - maxProjectedExtent;
    m_max      = origin + maxProjectedExtent;
}
