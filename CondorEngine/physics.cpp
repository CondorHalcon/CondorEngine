#include "physics.h"
#include "glm/ext.hpp"
#include "time.h"
#include "debug.h"
#include <string>

std::vector<CondorEngine::Collider *> CondorEngine::Physics::colliders = std::vector<CondorEngine::Collider *>();
std::vector<CondorEngine::Rigidbody *> CondorEngine::Physics::rigidbodies = std::vector<CondorEngine::Rigidbody *>();

void CondorEngine::Physics::init()
{
    colliders = std::vector<Collider*>();
    rigidbodies = std::vector<Rigidbody*>();
}

void CondorEngine::Physics::AddCollider(Collider *collider)
{
    colliders.push_back(collider);
}

void CondorEngine::Physics::RemoveCollider(Collider *collider)
{
    for (int i = 0; i < colliders.size(); i++) {
        if (colliders[i] == collider) {
            colliders.erase(std::next(colliders.begin(), i));
        }
    }
}

void CondorEngine::Physics::AddRigidbody(Rigidbody *rigidbody)
{
    rigidbodies.push_back(rigidbody);
}

void CondorEngine::Physics::RemoveRigidbody(Rigidbody *rigidbody)
{
    for (int i = 0; i < rigidbodies.size(); i++) {
        if (rigidbodies[i] == rigidbody) {
            rigidbodies.erase(std::next(rigidbodies.begin(), i));
        }
    }
}

void CondorEngine::Physics::PhysicsUpdate()
{
    // rigidbody
    for (int i = 0; i < rigidbodies.size(); i++) {
        rigidbodies[i]->getSceneObject()->Move(rigidbodies[i]->getVelocity() * Time::fixedDeltaTime());
    }

    // collision
    for (int i = 0; i < colliders.size() - 1; i++) {
        for (int j = i + 1; j < colliders.size(); j++) {
            // TODO collision check
            Vector3 offset = colliders[i]->getSceneObject()->getPosition() - colliders[j]->getSceneObject()->getPosition();
            float distance = glm::length(offset);
            /*Debug::Log(
                "colliders[" + std::to_string(i) + "] is " + std::to_string(distance) +
                " far from " +
                "colliders[" + std::to_string(j) + "]\n" +

                "colliders[" + std::to_string(i) + "]->radius " +
                std::to_string(colliders[i]->radius) + "; " +
                "colliders[" + std::to_string(j) + "]->radius " +
                std::to_string(colliders[j]->radius)
                );*/
            if (distance <= colliders[i]->radius + colliders[j]->radius) {
                Debug::Log("colliders[" + std::to_string(i) + "] is hitting " +
                "colliders[" + std::to_string(j) + "]" + 
                " at a distance of " +  std::to_string(distance)
                );

                // on collision triggers
                colliders[i]->getSceneObject()->ObjectOnCollision(colliders[j]);
                colliders[j]->getSceneObject()->ObjectOnCollision(colliders[i]);

                // collision resolution
                Rigidbody *rbA = nullptr;
                Rigidbody *rbB = nullptr;
                bool aHasRb = colliders[i]->getSceneObject()->TryFindComponent<Rigidbody>(rbA);
                //bool bHasRb = colliders[j]->getSceneObject()->TryFindComponent<Rigidbody>(rbB);
                Debug::Log(colliders[i]->name + ": " + std::to_string(aHasRb));
                if (aHasRb) 
                {
                    // TODO continue here
                }
            }
        }
    }
}
