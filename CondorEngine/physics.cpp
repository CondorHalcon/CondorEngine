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

#pragma region Physics Update
void CondorEngine::Physics::PhysicsUpdate()
{
    // rigidbody
    for (int i = 0; i < rigidbodies.size(); i++) {
        rigidbodies[i]->mass = rigidbodies[i]->mass <= 0 ? .001f : rigidbodies[i]->mass;
        if (!rigidbodies[i]->enabled) { continue; }
        rigidbodies[i]->getSceneObject()->Move(rigidbodies[i]->getVelocity() * Time::fixedDeltaTime());
    }

    // collision function pointers
    static CollisionCheckFn collisionChecks[] = {
        nullptr,                // 0 : Invalid
        nullptr,                // 1 : Sphere to Invalid
        sphereToSphereCheck,    // 2 : Sphere to Sphere
        planeToSphereCheck,     // 3 : Plane to Sphere
        nullptr,                // 4 : Plane to Plane
        aabbToSphereCheck,      // 5 : AABB to Sphere
        aabbToPlaneCheck,       // 6 : AABB to Plane
        nullptr,                // 7 : AABB to Invalid
        aabbToAABBCheck,        // 8 : AABB to AABB
        nullptr,                // 9 : Capsule to Sphere
        nullptr,                // 10 : Capsule to Plane
        nullptr,                // 11 : Capsule to Invalid
        nullptr,                // 12 : Capsule to AABB
        nullptr,                // 13 : Capsule to Invalid
        nullptr,                // 15 : Capsule to Invalid
        nullptr,                // 16 : Capsule to Capsule
    };
    static CollisionTriggerFn collisionTriggers[] = {
        nullptr,                // 0 : Invalid
        nullptr,                // 1 : Sphere to Invalid
        sphereToSphereTrigger,  // 2 : Sphere to Sphere
        planeToSphereTrigger,   // 3 : Plane to Sphere
        nullptr,                // 4 : Plane to Plane
        aabbToSphereTrigger,    // 5 : AABB to Sphere
        aabbToPlaneTrigger,     // 6 : AABB to Plane
        nullptr,                // 7 : AABB to Invalid
        aabbToAABBTrigger,      // 8 : AABB to AABB
        nullptr,                // 9 : Capsule to Sphere
        nullptr,                // 10 : Capsule to Plane
        nullptr,                // 11 : Capsule to Invalid
        nullptr,                // 12 : Capsule to AABB
        nullptr,                // 13 : Capsule to Invalid
        nullptr,                // 15 : Capsule to Invalid
        nullptr,                // 16 : Capsule to Capsule 
    };
    static CollisionResolutionFn collisionResolution[] = {
        nullptr,                    // 0 : Invalid
        nullptr,                    // 1 : Sphere to Invalid
        sphereToSphereResolution,   // 2 : Sphere to Sphere
        planeToSphereResolution,    // 3 : Plane to Sphere
        nullptr,                    // 4 : Plane to Plane
        aabbToSphereResolution,     // 5 : AABB to Sphere
        aabbToPlaneResolution,      // 6 : AABB to Plane
        nullptr,                    // 7 : AABB to Invalid
        aabbToAABBResolution,       // 8 : AABB to AABB
        nullptr,                    // 9 : Capsule to Sphere
        nullptr,                    // 10 : Capsule to Plane
        nullptr,                    // 11 : Capsule to Invalid
        nullptr,                    // 12 : Capsule to AABB
        nullptr,                    // 13 : Capsule to Invalid
        nullptr,                    // 15 : Capsule to Invalid
        nullptr,                    // 16 : Capsule to Capsule  
    };

    // collision
    for (int i = 0; i < colliders.size() - 1; i++)
    {
        for (int j = i + 1; j < colliders.size(); j++) {
            // collision check
            int typeSum = (int)colliders[i]->getType() + (int)colliders[j]->getType();
            CollisionCheckFn check = collisionChecks[typeSum];
            if (check == nullptr) { continue; } // no collision check implemented
            if (check(colliders[i], colliders[j])) {

                // on collision triggers
                CollisionResolutionFn trigger = collisionTriggers[typeSum];
                if (trigger != nullptr) {
                    trigger(colliders[i], colliders[j]);
                }

                // collision resolution
                CollisionResolutionFn resolution = collisionResolution[typeSum];
                if (resolution == nullptr) {
                    Debug::LogError("Physics::PhysicsUpdate() : Collision resolution not implemented for Collider types " + std::to_string(colliders[i]->getType()) + " and " + std::to_string(colliders[j]->getType()));
                    continue;
                }
                if (!colliders[i]->isTrigger && !colliders[j]->isTrigger) {
                    resolution(colliders[i], colliders[j]);
                }
            }
        }
    }
}
#pragma endregion

#pragma region SphereToSphere
bool CondorEngine::Physics::sphereToSphereCheck(Collider *collider1, Collider *collider2)
{
    Vector3 offset = collider1->getSceneObject()->getPosition() - collider2->getSceneObject()->getPosition();
    return glm::length(offset) <= collider1->radius + collider2->radius;
}

void CondorEngine::Physics::sphereToSphereTrigger(Collider *collider1, Collider *collider2)
{
    Vector3 normal = glm::normalize(collider1->getSceneObject()->getPosition() - collider2->getSceneObject()->getPosition());
    Rigidbody *rbA = collider1->getSceneObject()->GetComponentInParent<Rigidbody>();
    Rigidbody *rbB = collider2->getSceneObject()->GetComponentInParent<Rigidbody>();
    Vector3 relativeVelocity = (rbA != nullptr && rbA->enabled ? rbA->getVelocity() : Vector3{0,0,0}) - (rbB != nullptr && rbB->enabled ? rbB->getVelocity() : Vector3{0,0,0});
    collider1->getSceneObject()->ObjectOnCollision(Collision{ collider1, collider2, normal, relativeVelocity });
    collider2->getSceneObject()->ObjectOnCollision(Collision{ collider2, collider1, -normal, -relativeVelocity });
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
#pragma endregion

#pragma region PlaneToSphere
bool CondorEngine::Physics::planeToSphereCheck(Collider* collider1, Collider* collider2)
{
    Collider* plane = collider1->getType() == ColliderType::Plane ? collider1 : collider2;
    Collider* sphere = collider2->getType() == ColliderType::Sphere ? collider2 : collider1;

    /* D = dot(c - d, n) - r
        D is the distance from the sphere's center to the plane
        c is the sphere's center
        d is the plane's distance from the origin
        n is the plane's normal
        r is the sphere's radius */
    Vector3 c = sphere->getSceneObject()->getPosition();
    Vector3 d = plane->getSceneObject()->getPosition();
    Vector3 n = plane->plane.getNormal(plane->getSceneObject()->getTransform());
    float r = sphere->radius;
    float distance = glm::dot(c - d, n) - r;
    return distance <= 0 && distance >= -(r * 2);
}

void CondorEngine::Physics::planeToSphereTrigger(Collider *collider1, Collider *collider2)
{
    Collider* plane = collider1->getType() == ColliderType::Plane ? collider1 : collider2;
    Collider* sphere = collider2->getType() == ColliderType::Sphere ? collider2 : collider1;

    Vector3 normal = plane->plane.getNormal(plane->getSceneObject()->getTransform());
    Rigidbody *rbA = collider1->getSceneObject()->GetComponentInParent<Rigidbody>();
    Rigidbody *rbB = collider2->getSceneObject()->GetComponentInParent<Rigidbody>();
    Vector3 relativeVelocity = (rbA != nullptr && rbA->enabled ? rbA->getVelocity() : Vector3{0,0,0}) - (rbB != nullptr && rbB->enabled ? rbB->getVelocity() : Vector3{0,0,0});
    collider1->getSceneObject()->ObjectOnCollision(Collision{ collider1, collider2, normal, relativeVelocity });
    collider2->getSceneObject()->ObjectOnCollision(Collision{ collider2, collider1, -normal, -relativeVelocity });
}

void CondorEngine::Physics::planeToSphereResolution(Collider* collider1, Collider* collider2)
{
    Collider* plane = collider1->getType() == ColliderType::Plane ? collider1 : collider2;
    Collider* sphere = collider2->getType() == ColliderType::Sphere ? collider2 : collider1;

    // collision rigidbody
    Rigidbody* rb = sphere->getSceneObject()->GetComponentInParent<Rigidbody>();

    // collision resolution
    Vector3 normal = plane->plane.getNormal(plane->getSceneObject()->getTransform());
    float joules = glm::dot(2.0f * rb->velocity, normal) / glm::dot(normal, normal * (1 / rb->mass));
    rb->velocity -= joules * normal;
}

#pragma endregion

#pragma region AABBToSphere

bool CondorEngine::Physics::aabbToSphereCheck(Collider *collider1, Collider *collider2)
{
    Collider* aabb = collider1->getType() == ColliderType::AABB ? collider1 : collider2;
    Collider* sphere = collider2->getType() == ColliderType::Sphere ? collider2 : collider1;

    Vector3 offset = sphere->getSceneObject()->getPosition() - aabb->getClosestPoint(sphere->getSceneObject()->getPosition());

    float distanceSquared = glm::length(offset) * glm::length(offset);
    float radiusSquared = sphere->radius * sphere->radius;

    return distanceSquared <= radiusSquared;
}
void CondorEngine::Physics::aabbToSphereTrigger(Collider *collider1, Collider *collider2)
{
    Collider* aabb = collider1->getType() == ColliderType::AABB ? collider1 : collider2;
    Collider* sphere = collider2->getType() == ColliderType::Sphere ? collider2 : collider1;

    Vector3 normal = glm::normalize(sphere->getSceneObject()->getPosition() - aabb->getClosestPoint(sphere->getSceneObject()->getPosition()));
    Rigidbody *rbA = collider1->getSceneObject()->GetComponentInParent<Rigidbody>();
    Rigidbody *rbB = collider2->getSceneObject()->GetComponentInParent<Rigidbody>();
    Vector3 relativeVelocity = (rbA != nullptr && rbA->enabled ? rbA->getVelocity() : Vector3{0,0,0}) - (rbB != nullptr && rbB->enabled ? rbB->getVelocity() : Vector3{0,0,0});
    collider1->getSceneObject()->ObjectOnCollision(Collision{ collider1, collider2, normal, relativeVelocity });
    collider2->getSceneObject()->ObjectOnCollision(Collision{ collider2, collider1, -normal, -relativeVelocity });
}
void CondorEngine::Physics::aabbToSphereResolution(Collider *collider1, Collider *collider2)
{
    Collider* aabb = collider1->getType() == ColliderType::AABB ? collider1 : collider2;
    Collider* sphere = collider2->getType() == ColliderType::Sphere ? collider2 : collider1;

    // collision rigidbodies
    Rigidbody *rbA = collider1->getSceneObject()->GetComponentInParent<Rigidbody>();
    Rigidbody *rbB = collider2->getSceneObject()->GetComponentInParent<Rigidbody>();

    // collision resolution
    float joules = 0;
    Vector3 normal = glm::normalize(sphere->getSceneObject()->getPosition() - aabb->getClosestPoint(sphere->getSceneObject()->getPosition()));
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

#pragma endregion

#pragma region AABBToPlane

bool CondorEngine::Physics::aabbToPlaneCheck(Collider *collider1, Collider *collider2)
{
    Collider* aabb = collider1->getType() == ColliderType::AABB ? collider1 : collider2;
    Collider* plane = collider2->getType() == ColliderType::Plane ? collider2 : collider1;

    Vector3 planeClosestPoint = plane->getClosestPoint(aabb->getSceneObject()->getPosition());
    Vector3 aabbClosestPoint = aabb->getClosestPoint(planeClosestPoint);

    float aabbClosestPointDistance = glm::length(aabbClosestPoint - aabb->getSceneObject()->getPosition());

    /*Debug::Log(
        "\nplanePosition: " + to_string(plane->getSceneObject()->getPosition()) +
        "\naabbPosition: " + to_string(aabb->getSceneObject()->getPosition()) +
        "\n\nplaneClosestPoint: " + to_string(planeClosestPoint) +
        "\naabbClosestPoint: " + to_string(aabbClosestPoint) +
        "\n\naabbClosestPointDistance:" + std::to_string(aabbClosestPointDistance)
        );*/

    /* D = dot(c - d, n) - r
        D is the distance from the sphere's center to the plane
        c is the sphere's center
        d is the plane's distance from the origin
        n is the plane's normal
        r is the sphere's radius */
    Vector3 c = aabb->getSceneObject()->getPosition();
    Vector3 d = plane->getSceneObject()->getPosition();
    Vector3 n = plane->plane.getNormal(plane->getSceneObject()->getTransform());
    float r = aabbClosestPointDistance;
    float distance = glm::dot(c - d, n) - r;
    return distance <= 0 && distance >= -(r * 2);
}
void CondorEngine::Physics::aabbToPlaneTrigger(Collider *collider1, Collider *collider2)
{
    Collider* aabb = collider1->getType() == ColliderType::AABB ? collider1 : collider2;
    Collider* plane = collider2->getType() == ColliderType::Plane ? collider2 : collider1;

    Vector3 normal = plane->plane.getNormal(plane->getSceneObject()->getTransform());
    Rigidbody *rbA = collider1->getSceneObject()->GetComponentInParent<Rigidbody>();
    Rigidbody *rbB = collider2->getSceneObject()->GetComponentInParent<Rigidbody>();
    Vector3 relativeVelocity = (rbA != nullptr && rbA->enabled ? rbA->getVelocity() : Vector3{0,0,0}) - (rbB != nullptr && rbB->enabled ? rbB->getVelocity() : Vector3{0,0,0});
    aabb->getSceneObject()->ObjectOnCollision(Collision{ collider1, collider2, normal, relativeVelocity });
    plane->getSceneObject()->ObjectOnCollision(Collision{ collider2, collider1, -normal, -relativeVelocity });
}
void CondorEngine::Physics::aabbToPlaneResolution(Collider *collider1, Collider *collider2)
{
    Collider* aabb = collider1->getType() == ColliderType::AABB ? collider1 : collider2;
    Collider* plane = collider2->getType() == ColliderType::Plane ? collider2 : collider1;

    // collision rigidbody
    Rigidbody* rb = aabb->getSceneObject()->GetComponentInParent<Rigidbody>();

    // collision resolution
    Vector3 normal = plane->plane.getNormal(plane->getSceneObject()->getTransform());
    float joules = glm::dot(2.0f * rb->velocity, normal) / glm::dot(normal, normal * (1 / rb->mass));
    rb->velocity -= joules * normal;
}

#pragma endregion

#pragma region AABBToAABB

bool CondorEngine::Physics::aabbToAABBCheck(Collider *collider1, Collider *collider2)
{
    Vector3 aabb1Min = collider1->getSceneObject()->getPosition() - collider1->size * .5f;
    Vector3 aabb1Max = collider1->getSceneObject()->getPosition() + collider1->size * .5f;
    Vector3 aabb2Min = collider2->getSceneObject()->getPosition() - collider2->size * .5f;
    Vector3 aabb2Max = collider2->getSceneObject()->getPosition() + collider2->size * .5f;

    return aabb1Min.x <= aabb2Max.x && aabb1Max.x >= aabb2Min.x &&
        aabb1Min.y <= aabb2Max.y && aabb1Max.y >= aabb2Min.y &&
        aabb1Min.z <= aabb2Max.z && aabb1Max.z >= aabb2Min.z;
}
void CondorEngine::Physics::aabbToAABBTrigger(Collider *collider1, Collider *collider2)
{
    Debug::Log("aabbToAABBTrigger");
    Vector3 normal = glm::normalize(collider1->getSceneObject()->getPosition() - collider2->getSceneObject()->getPosition());
    Rigidbody *rbA = collider1->getSceneObject()->GetComponentInParent<Rigidbody>();
    Rigidbody *rbB = collider2->getSceneObject()->GetComponentInParent<Rigidbody>();
    Vector3 relativeVelocity = (rbA != nullptr && rbA->enabled ? rbA->getVelocity() : Vector3{0,0,0}) - (rbB != nullptr && rbB->enabled ? rbB->getVelocity() : Vector3{0,0,0});
    collider1->getSceneObject()->ObjectOnCollision(Collision{ collider1, collider2, normal, relativeVelocity });
    collider2->getSceneObject()->ObjectOnCollision(Collision{ collider2, collider1, -normal, -relativeVelocity });
}
void CondorEngine::Physics::aabbToAABBResolution(Collider *collider1, Collider *collider2)
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

#pragma endregion
