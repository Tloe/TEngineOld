#include <TEBVH.h>
#include <TECollisionComponent.h>
#include <TEContactGenerator.h>
#include <TEContactSet.h>
#include <TEPhysicsComponent.h>
#include <TEPlane.h>
#include <TEPotentialContact.h>

void TE::CollisionDetection::ContactGenerator::GenerateContacts(
    std::unordered_map<I32, Physics::PhysicsComponent> &physicsComponents,
    std::unordered_map<I32, CollisionComponent> &collisionComponents,
    std::vector<Intersection::ContactSet> &contactSets,
    Real dt) {
    /*std::vector<CollisionComponent*> planes;
    BVHNode treeRoot;

    CreatePlaneVectorAndTree(collisionComponents, planes, treeRoot);
    std::vector<PotentialContact> potentialContacts;
    if (treeRoot) treeRoot->GetPotentialContacts(potentialContacts);
    FullCheckPotentialContacts(potentialContacts, physicsComponents, collisionComponents, dt,
    contactSets); CheckObjectsAgainstPlanes(planes, collisionComponents, contactSets);*/
}

void TE::CollisionDetection::ContactGenerator::CreatePlaneVectorAndTree(
    std::unordered_map<I32, CollisionDetection::CollisionComponent> &collisionComponents,
    std::vector<CollisionComponent *> &planes,
    BVHNode &treeRoot) {
    /*std::unordered_map<I32, CollisionDetection::CollisionComponent>::iterator componentsIter =
    collisionComponents.begin();

    while (componentsIter != collisionComponents.end())
    {
            if (componentsIter->second->IsPlane())
                    //Add to Plane vector
                    planes.push_back(&componentsIter->second);
            else if(!treeRoot)
                    //Create first tree node
                    treeRoot = new0 BVHNode(NULL, *componentsIter->second.GetEnclosing(),
    componentsIter->second.GetComponentId()); else
                    //Insert into tree
                    treeRoot = new0 BVHNode(NULL, *componentsIter->second.GetEnclosing(),
    componentsIter->second.GetComponentId());

            ++componentsIter;
    }*/
}

void TE::CollisionDetection::ContactGenerator::CheckObjectsAgainstPlanes(
    std::vector<CollisionComponent *> &planes,
    std::unordered_map<I32, CollisionComponent> &collisionComponents,
    std::vector<Intersection::ContactSet> &contactSets) {
    std::unordered_map<I32, CollisionDetection::CollisionComponent>::iterator componentsIter;
    for (unsigned i = 0; i < planes.size(); i++) {
        componentsIter = collisionComponents.begin();
        while (componentsIter != collisionComponents.end()) {
            Intersection::ContactSet newContactSet;
            // bool collision = componentsIter->second.CollisionCheckFull(*planes[i],newContactSet);

            // if(collision) contactSets.push_back(newContactSet);
        }
    }
}

void TE::CollisionDetection::ContactGenerator::FullCheckPotentialContacts(
    std::vector<PotentialContact> &potentialContacts,
    std::unordered_map<I32, Physics::PhysicsComponent> &physicsComponents,
    std::unordered_map<I32, CollisionComponent> &collisionComponents,
    Real dt,
    std::vector<Intersection::ContactSet> &contactSets) {
    for (unsigned i = 0; i < potentialContacts.size(); i++) {
        // Intersection::ContactSet newContactSet;
        // Physics::PhysicsComponent& physcomp0 = physicsComponents[ potentialContacts[i].entityId0
        // ]; Physics::PhysicsComponent& physcomp1 = physicsComponents[
        // potentialContacts[i].entityId1 ];

        /*bool collision = collisionComponents[ potentialContacts[i].entityId0 ].CollisionCheckFull(
                collisionComponents[ potentialContacts[i].entityId1 ],
                newContactSet,
                dt,
                &physcomp0.GetPosition(),
                &physcomp1.GetPosition(),
                &physcomp0.GetVelocity(),
                &physcomp1.GetVelocity(),
                &physcomp0.GetAngularVelocity(),
                &physcomp1.GetAngularVelocity());

        if(collision) contactSets.push_back(newContactSet);*/
    }
}
