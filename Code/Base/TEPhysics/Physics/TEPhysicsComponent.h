#ifndef TEPHYSICSCOMPONENT_H
#define TEPHYSICSCOMPONENT_H

#include <TEVector3D.h>

namespace TE::Physics {
    class PhysicsComponent {
      public:
        void Update();
        const Math::Vector3D<Real> &GetPosition() { return m_position; }
        const Math::Vector3D<Real> &GetVelocity() { return m_velocity; }
        const Math::Vector3D<Real> &GetAngularVelocity() { return m_angularVelocity; }

      private:
        Math::Vector3D<Real> m_position;
        Math::Vector3D<Real> m_velocity;
        Math::Vector3D<Real> m_angularVelocity;
    };
}

#endif
