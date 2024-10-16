#include "physics.h"
// internal
#include "time.h"
#include "debug.hpp"
#include "sceneobject.h"
// std
#include <string>
// third party
#include "glm/ext.hpp"

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
        rigidbodies[i]->mass = rigidbodies[i]->mass <= 0 ? .001f : rigidbodies[i]->mass;
        if (!rigidbodies[i]->enabled) { continue; }
        rigidbodies[i]->getSceneObject()->Move(rigidbodies[i]->getVelocity() * Time::fixedDeltaTime());
    }

    // collision

    static CollisionCheckFn collisionChecks[] = {
        sphereToSphereCheck,
        sphereToPlaneCheck
    };
    static CollisionResolutionFn collisionResolution[] = {
        sphereToSphereResolution,
        sphereToPlaneResolution
    };

    for (int i = 0; i < colliders.size() - 1; i++)
    {
        for (int j = i + 1; j < colliders.size(); j++) {
            // collision check
            int typeSum = (int)colliders[i]->getType() + (int)colliders[j]->getType();
            CollisionCheckFn check = collisionChecks[typeSum];
            if (check == nullptr) {
                Debug::LogError("Physics::PhysicsUpdate() : Collision check not implemented for Collider types " + std::to_string(colliders[i]->getType()) + " and " + std::to_string(colliders[j]->getType()));
                continue; 
            }
            if (check(colliders[i], colliders[j])) {
                Debug::LogError("Physics::PhysicsUpdate() : Collision check ["+ std::to_string(typeSum) + "] for Collider types " + std::to_string(colliders[i]->getType()) + " and " + std::to_string(colliders[j]->getType()));
                // on collision triggers
                colliders[i]->getSceneObject()->ObjectOnCollision(colliders[j]);
                colliders[j]->getSceneObject()->ObjectOnCollision(colliders[i]);

                // collision resolution
                CollisionResolutionFn resolution = collisionResolution[typeSum];
                if (resolution == nullptr) {
                    Debug::LogError("Physics::PhysicsUpdate() : Collision resolution not implemented for Collider types " + std::to_string(colliders[i]->getType()) + " and " + std::to_string(colliders[j]->getType()));
                    continue;
                }
                resolution(colliders[i], colliders[j]);
            }
        }
    }
}

bool CondorEngine::Physics::sphereToSphereCheck(Collider *collider1, Collider *collider2)
{
    Vector3 offset = collider1->getSceneObject()->getPosition() - collider2->getSceneObject()->getPosition();
    return glm::length(offset) <= collider1->radius + collider2->radius;
}

void CondorEngine::Physics::sphereToSphereResolution(Collider *collider1, Collider *collider2)
{
    // collision rigidbodies
    Rigidbody *rbA = collider1->getSceneObject()->GetComponentInParent<Rigidbody>();
    Rigidbody *rbB = collider2->getSceneObject()->GetComponentInParent<Rigidbody>();

    // collision resolution
    float joules = 0;
    Vector3 normal = glm::normalize(collider1->getSceneObject()->getPosition() - collider2->getSceneObject()->getPosition());
    if ((rbA != nullptr && rbA->enabled) && (rbB != nullptr && rbB->enabled)) 
    {
        joules = glm::dot(2.0f * (rbA->velocity - rbB->velocity), normal) / glm::dot(normal, normal * ((1 / rbA->mass) + (1 / rbB->mass)));
        rbA->velocity -= (joules / rbA->mass) * normal;
        rbB->velocity += (joules / rbB->mass) * normal;
    } 
    else if (rbA != nullptr && rbA->enabled) {
        joules = glm::dot(2.0f * rbA->velocity, normal) / glm::dot(normal, normal * (1 / rbA->mass));
        rbA->velocity -= joules * normal;
    } 
    else if (rbB != nullptr && rbB->enabled) {
        joules = glm::dot(2.0f * rbB->velocity, normal) / glm::dot(normal, normal * (1 / rbB->mass));
        rbB->velocity -= joules * normal;
    }
}

bool CondorEngine::Physics::sphereToPlaneCheck(Collider* collider1, Collider* collider2)
{
    Collider* plane = collider1->getType() == ColliderType::Plane ? collider1 : collider2;
    Collider* sphere = collider2->getType() == ColliderType::Sphere ? collider2 : collider1;

    /* D = dot(c - d, n) - r
        D is the distance from the sphere's center to the plane
        c is the sphere's center
        n is the plane's normal
        d is the plane's distance from the origin
        r is the sphere's radius */
    float distance = glm::dot(sphere->getSceneObject()->getPosition() - plane->getSceneObject()->getPosition(), plane->getSceneObject()->getUp()) - sphere->radius;
    return distance <= 0 && distance >= -(sphere->radius * 2);
}

void CondorEngine::Physics::sphereToPlaneResolution(Collider* collider1, Collider* collider2)
{
    Collider* plane = collider1->getType() == ColliderType::Plane ? collider1 : collider2;
    Collider* sphere = collider2->getType() == ColliderType::Sphere ? collider2 : collider1;

    Debug::Log("Physics::sphereToPlaneResolution() : distance = " + std::to_string(glm::dot(sphere->getSceneObject()->getPosition() - plane->getSceneObject()->getPosition(), plane->getSceneObject()->getUp()) - sphere->radius));
}
