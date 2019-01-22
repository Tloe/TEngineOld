#ifndef TEBVH_H
#define TEBVH_H

#include <TEBSphere.h>
#include <string>
#include <vector>

namespace TE
{
	namespace CollisionDetection { struct PotentialContact; }

	namespace CollisionDetection
	{
		class BVHNode
		{
		public:
			BVHNode(BVHNode *parent, Intersection::BSphere bVol, I32 entityId);

			~BVHNode();
			void GetPotentialContacts(std::vector<PotentialContact> &potentialContacts);
			void Insert(I32 entityId, Intersection::BSphere &boundingVolume);
		private:
			void GetPotentialContactsWith(BVHNode *other, std::vector<PotentialContact> &potentialContacts);
			void RecalculateBoundingVolume(bool recurse = true);
			bool IsLeaf();
			bool CheckOverlap(BVHNode *other);

			BVHNode*				m_parent;
			BVHNode*				m_child0;
			BVHNode*				m_child1;
			Intersection::BSphere	m_boundingVol;
			I32						m_entityId;
		};
	}
}

#endif