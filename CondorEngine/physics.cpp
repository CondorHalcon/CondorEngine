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
            // collision check
            Vector3 offset = colliders[i]->getSceneObject()->getPosition() - colliders[j]->getSceneObject()->getPosition();
            float distance = glm::length(offset);
            if (distance <= colliders[i]->radius + colliders[j]->radius) {
                Debug::Log("colliders[" + std::to_string(i) + "] is hitting " +
                "colliders[" + std::to_string(j) + "]" + 
                " at a distance of " +  std::to_string(distance)
                );

                // on collision triggers
                colliders[i]->getSceneObject()->ObjectOnCollision(colliders[j]);
                colliders[j]->getSceneObject()->ObjectOnCollision(colliders[i]);

                // collision rigidbodies
                Rigidbody *rbA = colliders[i]->getSceneObject()->GetComponentInParent<Rigidbody>();
                Rigidbody *rbB = colliders[j]->getSceneObject()->GetComponentInParent<Rigidbody>();

                // collision resolution
                Vector3 normal = glm::normalize(offset);
                if ((rbA != nullptr && rbA->enabled) && (rbB != nullptr && rbB->enabled)) 
                {
                    float joules = glm::dot(2.0f * (rbA->velocity - rbB->velocity), normal) / glm::dot(normal, normal * ((1 / rbA->mass) + (1 / rbB->mass)));
                    rbA->velocity -= (joules / rbA->mass) * normal;
                    rbB->velocity += (joules / rbB->mass) * normal;
                } 
                else if (rbA != nullptr && rbA->enabled) {
                    float joules = glm::dot(2.0f * rbA->velocity, normal) / glm::dot(normal, normal * (1 / rbA->mass));
                    rbA->velocity -= joules * normal;
                } 
                else if (rbB != nullptr && rbB->enabled) {
                    float joules = glm::dot(2.0f * rbB->velocity, normal) / glm::dot(normal, normal * (1 / rbB->mass));
                    rbB->velocity -= joules * normal;
                }
            }
        }
    }
}
