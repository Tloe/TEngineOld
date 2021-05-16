#ifndef TECOLLIDERVISITOR_H
#define TECOLLIDERVISITOR_H

#include <TEDataTypes.h>
#include <TEMathBase.h>

namespace TE {
    namespace Math {
        template <typename T>
        class Vector3D;
    }
    namespace Intersection {
        struct ContactSet;
    }
    namespace Intersection {
        struct Obb;
    }
    namespace Intersection {
        struct BSphere;
    }
    namespace Intersection {
        struct Plane;
    }

    namespace Intersection {
        class ColliderVisitor {
          public:
            ColliderVisitor(bool coarse, Real dt = Math::Base<Real>::REAL_ZERO,
                            ContactSet *contactSet           = NULL,
                            const Math::Vector3D<Real> *pos0 = NULL, const Math::Vector3D<Real> *pos1 = NULL,
                            const Math::Vector3D<Real> *vel0 = NULL, const Math::Vector3D<Real> *vel1 = NULL,
                            const Math::Vector3D<Real> *angvel0 = NULL, const Math::Vector3D<Real> *angvel1 = NULL)
                : m_coarse(coarse),
                  m_dt(dt),
                  m_contactSet(contactSet),
                  m_pos0(pos0),
                  m_pos1(pos1),
                  m_vel0(vel0),
                  m_vel1(vel1),
                  m_angvel0(angvel0),
                  m_angvel1(angvel1) {}

            bool operator()(Obb &obb, Plane &plane);
            bool operator()(Obb &obb, BSphere &bsphere);
            bool operator()(Obb &obb0, Obb &obb1);

            bool operator()(Plane &plane, Obb &obb);
            bool operator()(Plane &plane, BSphere &bsphere);
            bool operator()(Plane &plane0, Plane &plane1);

            bool operator()(BSphere &bsphere, Obb &obb);
            bool operator()(BSphere &bsphere, Plane &plane);
            bool operator()(BSphere &bsphere0, BSphere &bsphere1);

          private:
            bool m_coarse;
            Real m_dt;
            ContactSet *m_contactSet;
            const Math::Vector3D<Real> *m_pos0;
            const Math::Vector3D<Real> *m_pos1;
            const Math::Vector3D<Real> *m_vel0;
            const Math::Vector3D<Real> *m_vel1;
            const Math::Vector3D<Real> *m_angvel0;
            const Math::Vector3D<Real> *m_angvel1;
        };
    }
}

#endif
