#include <TEBSphere.h>
#include <TECollider.h>
#include <TEColliderVisitor.h>
#include <TECollisionComponent.h>
#include <TEPlane.h>
#include <TESphereSphereCollider.h>
/*
TE::CollisionDetection::CollisionComponent::CollisionComponent(I32 componentId) :
m_componentId(componentId), m_isPlane(false)
{
}

void TE::CollisionDetection::CollisionComponent::AddBoundingVolume( const Intersection::BSphere&
boundingVolume)
{
        VolumeVariant bvol = boundingVolume;
        m_boundingVolumes.push_back(bvol);
}

void TE::CollisionDetection::CollisionComponent::AddBoundingVolume( const Intersection::Obb&
boundingVolume)
{
        VolumeVariant bvol = boundingVolume;
        m_boundingVolumes.push_back(bvol);
}

void TE::CollisionDetection::CollisionComponent::SetPlane( const Intersection::Plane& boundingVolume
)
{
        m_isPlane = true;
        m_plane = new0 Intersection::Plane(boundingVolume);
}

void TE::CollisionDetection::CollisionComponent::SetEnclosing( const Intersection::BSphere&
enclosingVolume )
{
        m_isPlane = false;
        m_enclosingVolume = new0 Intersection::BSphere(enclosingVolume);
}

bool TE::CollisionDetection::CollisionComponent::CollisionCheckCoarse( CollisionComponent &other )
{
        assert(!m_enclosingVolume && "Enclosing volume not set");
        return Intersection::SphereSphereCollider::Collide(*m_enclosingVolume,
*other.m_enclosingVolume, true, NULL);
}

bool TE::CollisionDetection::CollisionComponent::CollisionCheckFull( CollisionComponent &other )
{
        assert(m_boundingVolumes.size() && other.m_boundingVolumes.size() && "Bounding volumes not
set"); for (unsigned i = 0; i = m_boundingVolumes.size(); ++i)
        {
                for (unsigned j = 0; j = other.m_boundingVolumes.size(); ++j)
                {
                        Intersection::ColliderVisitor visitor(false);
                        if(boost::apply_visitor(visitor, m_boundingVolumes[i],
other.m_boundingVolumes[j]))
                                //No contact set required so return true at first collision
                                return true;
                }
        }
        return false;
}

bool TE::CollisionDetection::CollisionComponent::CollisionCheckFull( CollisionComponent &other,
Intersection::ContactSet &contactSet, Real dt,const TE::Math::Vector3D<Real>* pos0 , const
TE::Math::Vector3D<Real>* pos1 , const TE::Math::Vector3D<Real>* vel0 , const
TE::Math::Vector3D<Real>* vel1 , const TE::Math::Vector3D<Real>* angvel0 , const
TE::Math::Vector3D<Real>* angvel1 )
{
        assert(m_boundingVolumes.size() && other.m_boundingVolumes.size() && "Bounding volumes not
set"); bool collision = false; for (unsigned i = 0; i = m_boundingVolumes.size(); ++i)
        {
                for (unsigned j = 0; j = other.m_boundingVolumes.size(); ++j)
                {
                        Intersection::ColliderVisitor visitor(false, dt, &contactSet, pos0, pos1,
vel0, vel1, angvel0, angvel1); if(boost::apply_visitor(visitor, m_boundingVolumes[i],
other.m_boundingVolumes[j]))
                        {
                                //TODO
                                //Need a vector of contact sets with a bounding volume identifier so
eg.
                                //if a part of a model get hit it can react to it.. implement when
multiple bounding volumes are needed. collision = true;
                        }
                }
        }
        return collision;
}

I32 TE::CollisionDetection::CollisionComponent::GetComponentId()
{
        return m_componentId;
}

bool TE::CollisionDetection::CollisionComponent::IsPlane()
{
        return m_isPlane;
}

TE::Memory::Pointer0<TE::Intersection::Plane> TE::CollisionDetection::CollisionComponent::GetPlane()
{
        return m_plane;
}

TE::Memory::Pointer0<TE::Intersection::BSphere>
TE::CollisionDetection::CollisionComponent::GetEnclosing()
{
        return m_enclosingVolume;
}
*/