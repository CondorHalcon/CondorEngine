#pragma once
// third party
#include "math.h"
#include "components/rigidbody.h"
#include "components/collider.h"
// std
#include <vector>

namespace CondorEngine
{
    /// @brief Collision check function pointer.
    typedef bool(*CollisionCheckFn)(Collider* collider1, Collider* collider2);
    /// @brief Collision trigger function pointer.
    typedef void(*CollisionTriggerFn)(Collider* collider1, Collider* collider2);
    /// @brief Collision resolution function pointer.
    typedef void(*CollisionResolutionFn)(Collider* collider1, Collider* collider2);

    /// @brief Collision data structure.
    struct Collision
    {
        Collider *collider;
        Collider *other;
        Vector3 normal;
        Vector3 relativeVelocity;
    };

    /// @brief Engine physics class.
    class Physics
    {
    public:
        /// @brief Initialize the physics engine.
        static void init();
    private:
        /// @brief List of all colliders in the scene.
        static std::vector<Collider*> colliders;
        /// @brief List of all the rigidbodies in the scene.
        static std::vector<Rigidbody*> rigidbodies;
    public:
        /// @brief Add a collider to the physics engine.
        static void AddCollider(Collider* collider);
        /// @brief Remove a collider from the physics engine.
        static void RemoveCollider(Collider *collider);
        /// @brief Add a rigidbody to the physics engine.
        static void AddRigidbody(Rigidbody* rigidbody);
        /// @brief Remove a rigidbody from the physics engine.
        static void RemoveRigidbody(Rigidbody *rigidbody);
        /// @brief Update the physics engine.
        static void PhysicsUpdate();
    private:
        static bool sphereToSphereCheck(Collider* collider1, Collider* collider2);
        static void sphereToSphereTrigger(Collider* collider1, Collider* collider2);
        static void sphereToSphereResolution(Collider* collider1, Collider* collider2);
        static bool sphereToPlaneCheck(Collider* collider1, Collider* collider2);
        static void sphereToPlaneTrigger(Collider* collider1, Collider* collider2);
        static void sphereToPlaneResolution(Collider* collider1, Collider* collider2);
    };
}
