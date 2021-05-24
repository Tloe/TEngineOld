#include <TEBVH.h>
#include <TEPotentialContact.h>
#include <TESphereSphereCollider.h>

TE::CollisionDetection::BVHNode::BVHNode(BVHNode *parent, Intersection::BSphere bVol, I32 entityId)
    : m_parent(parent),
      m_boundingVol(bVol),
      m_entityId(entityId) {}

TE::CollisionDetection::BVHNode::~BVHNode() {
    if (m_parent) {
        BVHNode *sibling;
        if (m_parent->m_child0 == this)
            sibling = m_parent->m_child1;
        else
            sibling = m_parent->m_child0;

        m_parent->m_boundingVol = sibling->m_boundingVol;
        m_parent->m_entityId    = sibling->m_entityId;
        m_parent->m_child0      = sibling->m_child0;
        m_parent->m_child1      = sibling->m_child1;

        sibling->m_parent       = NULL;
        sibling->m_child0       = NULL;
        sibling->m_child1       = NULL;
        delete sibling;

        m_parent->RecalculateBoundingVolume();
    }

    if (m_child0) {
        m_child0->m_parent = NULL;
        delete m_child0;
    }
    if (m_child1) {
        m_child1->m_parent = NULL;
        delete m_child1;
    }
}

void TE::CollisionDetection::BVHNode::GetPotentialContacts(
    std::vector<PotentialContact> &potentialContacts) {
    if (IsLeaf())
        return;

    m_child0->GetPotentialContactsWith(m_child1, potentialContacts);
}

void TE::CollisionDetection::BVHNode::Insert(I32 entityId, Intersection::BSphere &boundingVolume) {
    if (IsLeaf()) {
        m_child0         = new BVHNode(this, m_boundingVol, m_entityId);

        m_child1         = new BVHNode(this, boundingVolume, entityId);

        this->m_entityId = -1;

        RecalculateBoundingVolume();
    } else {
        Intersection::BSphere tempVolume0 = m_child0->m_boundingVol;
        Intersection::BSphere tempVolume1 = m_child1->m_boundingVol;
        Grow(tempVolume0, boundingVolume);
        Grow(tempVolume1, boundingVolume);
        if (Size(tempVolume0) < Size(tempVolume1))
            m_child0->Insert(entityId, boundingVolume);
        else
            m_child1->Insert(entityId, boundingVolume);
    }
}

void TE::CollisionDetection::BVHNode::GetPotentialContactsWith(
    BVHNode *other,
    std::vector<PotentialContact> &potentialContacts) {
    // I think I spent almost a week getting this function right. thats why its so well commented :)
    bool overlaps = CheckOverlap(other);

    // If bounding volume of this and the other overlaps and the two nodes are leaf's theres a new
    // contact
    if (overlaps && IsLeaf() && other->IsLeaf()) {
        PotentialContact potentialContact;
        potentialContact.entityId0 = m_entityId;
        potentialContact.entityId1 = other->m_entityId;
        potentialContacts.push_back(potentialContact);
        return;
    }

    // If it overlaps and still reach this, it means one of the nodes are leaf and the other is not.
    // We traverse down the tree checking either this against the other's children or the other with
    // the children of this.
    if (overlaps) {
        if (IsLeaf()) {
            GetPotentialContactsWith(other->m_child0, potentialContacts);
            GetPotentialContactsWith(other->m_child1, potentialContacts);
        } else {
            other->GetPotentialContactsWith(m_child0, potentialContacts);
            other->GetPotentialContactsWith(m_child1, potentialContacts);
        }
    }

    // This part continue traversal down the tree. If the parent of the two nodes are not the same
    // it means that we are on the path to find contacts with one node and the branch of the
    // other(The recursion started in the previous if statement) and we should not check the branch
    // of each node. This will be done once the other recursion completes(again, the one started in
    // the previous if statement)
    if (m_parent == other->m_parent) {
        if (!IsLeaf())
            m_child0->GetPotentialContactsWith(m_child1, potentialContacts);
        if (!other->IsLeaf())
            other->m_child0->GetPotentialContactsWith(other->m_child1, potentialContacts);
    }
}

void TE::CollisionDetection::BVHNode::RecalculateBoundingVolume(bool recurse /*= true*/) {
    assert(false && "Debug: recurse is never checked? is it right to default to true? Check all "
                    "calls to this function");

    if (IsLeaf())
        return;

    m_boundingVol = m_child0->m_boundingVol;
    Grow(m_boundingVol, m_child1->m_boundingVol);

    // Recurse up the tree
    if (m_parent)
        m_parent->RecalculateBoundingVolume(true);
}

bool TE::CollisionDetection::BVHNode::IsLeaf() { return m_entityId != -1; }

bool TE::CollisionDetection::BVHNode::CheckOverlap(BVHNode *other) {
    if (IsLeaf() && other->IsLeaf())
        return false;

    return Intersection::SphereSphereCollider::Collide(m_boundingVol, other->m_boundingVol, true,
                                                       NULL);
}
