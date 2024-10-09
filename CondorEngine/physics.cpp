#include "physics.h"
#include "glm/ext.hpp"

void CondorEngine::Physics::init()
{
    colliders = std::vector<Collider*>();
    rigidbodies = std::vector<Rigidbody*>();
}

void CondorEngine::Physics::AddCollider(Collider *collider)
{
    colliders.push_back(collider);
}

void CondorEngine::Physics::AddRigidbody(Rigidbody *rigidbody)
{
    rigidbodies.push_back(rigidbody);
}

void CondorEngine::Physics::PhysicsUpdate()
{
    // rigidbody
    for (int i = 0; i < rigidbodies.size(); i++) {
        rigidbodies[i]->getSceneObject()->Move(rigidbodies[i]->getVelocity());
    }
    rigidbodies.clear();

    // collision
    for (int i = 0; i < colliders.size() - 1; i++) {
        for (int j = i + 1; j < colliders.size(); j++) {
            // TODO collision check
            Vector3 offset = colliders[i]->getSceneObject()->getPosition() - colliders[j]->getSceneObject()->getPosition();
            float distance = glm::length(offset);
            if (distance < colliders[i]->radius + colliders[j]->radius) {
                colliders[i]->getSceneObject()->ObjectOnCollision(colliders[j]);
                colliders[j]->getSceneObject()->ObjectOnCollision(colliders[i]);
            }
        }
    }
    colliders.clear();
}
