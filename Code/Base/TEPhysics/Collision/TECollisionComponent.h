#ifndef TECOLLISIONCOMPONENT_H
#define TECOLLISIONCOMPONENT_H

#include <TEBoundingVolumeCommon.h>
#include <vector>

namespace TE::Math {
    template <typename T> class Vector3D;
}

namespace TE::Intersection {
    struct BSphere;
    struct Obb;
    struct Plane;
    struct ContactSet;
}

namespace TE::CollisionDetection {
    class CollisionComponent {
        /*public:
                CollisionComponent(I32 componentId = -1);
                void AddBoundingVolume(const Intersection::BSphere& boundingVolume);
                void AddBoundingVolume(const Intersection::Obb& boundingVolume);
                void SetPlane(const Intersection::Plane& boundingVolume);
                Memory::Pointer0<Intersection::Plane> GetPlane();

                void SetEnclosing(const Intersection::BSphere& enclosingVolume);
                Memory::Pointer0<Intersection::BSphere> GetEnclosing();

                bool IsPlane();

                I32 GetComponentId();

                bool CollisionCheckCoarse(CollisionComponent &other);
                bool CollisionCheckFull(CollisionComponent &other);
                bool CollisionCheckFull(CollisionComponent &other, Intersection::ContactSet
        &contactSet, Real dt = Math::Base<Real>::REAL_ZERO, const Math::Vector3D<Real>* pos0 =
        NULL, const Math::Vector3D<Real>* pos1 = NULL, const Math::Vector3D<Real>* vel0 = NULL,
        const Math::Vector3D<Real>* vel1 = NULL, const Math::Vector3D<Real>* angvel0 = NULL,
        const Math::Vector3D<Real>* angvel1 = NULL);

        private:
                bool m_isPlane; I32
        m_componentId; Memory::Pointer0<Intersection::BSphere>	m_enclosingVolume;
                Memory::Pointer0<Intersection::Plane>	m_plane;
                std::vector<VolumeVariant>				m_boundingVolumes;
                */
    };
}

#endif
