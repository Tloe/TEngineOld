#ifndef TECONTACTGENERATOR_H
#define TECONTACTGENERATOR_H

#include <TEDataTypes.h>
#include <unordered_map>
#include <vector>

namespace TE
{
	namespace Physics
	{
		class PhysicsComponent;
	}

	namespace Intersection
	{
		struct ContactSet;
	}
	namespace CollisionDetection
	{
		class CollisionComponent;
		class BVHNode;
		struct PotentialContact;

		class ContactGenerator
		{
		public:
			void GenerateContacts(std::unordered_map<I32, Physics::PhysicsComponent>& physicsComponents, std::unordered_map<I32, CollisionComponent>& collisionComponents, std::vector<Intersection::ContactSet>& contactSets, Real dt);
		private:
			void CreatePlaneVectorAndTree(std::unordered_map<I32, CollisionComponent>& collisionComponents, std::vector<CollisionComponent*>& planes, BVHNode& treeRoot);
			void CheckObjectsAgainstPlanes( std::vector<CollisionComponent*> &planes, std::unordered_map<I32, CollisionComponent> &collisionComponents, std::vector<Intersection::ContactSet> &contactSets );
			void FullCheckPotentialContacts( std::vector<PotentialContact> &potentialContacts, std::unordered_map<I32, Physics::PhysicsComponent> &physicsComponents, std::unordered_map<I32, CollisionComponent> &collisionComponents, Real dt, std::vector<Intersection::ContactSet> &contactSets );
		};
	}
}

#endif
