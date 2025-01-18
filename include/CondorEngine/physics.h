#pragma once
#include "CondorEngine/pch.h"
// third party
#include "CondorEngine/math.hpp"
#include "CondorEngine/components/rigidbody.h"
#include "CondorEngine/components/collider.h"
// std
#include <vector>

namespace CondorEngine
{
    /// @brief Collision check function pointer.
    typedef DllExport bool (*CollisionCheckFn)(Collider *collider1, Collider *collider2);
    /// @brief Collision trigger function pointer.
    typedef DllExport void (*CollisionTriggerFn)(Collider *collider1, Collider *collider2);
    /// @brief Collision resolution function pointer.
    typedef DllExport void (*CollisionResolutionFn)(Collider *collider1, Collider *collider2);

    /// @brief Collision data structure.
    struct Collision
    {
        Collider *collider;
        Collider *other;
        Vector3 normal;
        Vector3 relativeVelocity;
        bool isTriggerOnly();
    };

    /// @brief Engine physics class.
    class Physics
    {
    public:
        /// @brief Depenetrate if collision joules are bellow this threshold.
        static float depenetrationThreshold;
        /// @brief Initialize the physics engine.
        static void init();

    private:
        /// @brief List of all colliders in the scene.
        static std::vector<Collider *> colliders;
        /// @brief List of all the rigidbodies in the scene.
        static std::vector<Rigidbody *> rigidbodies;

    public:
        /// @brief Add a collider to the physics engine.
        static void AddCollider(Collider *collider);
        /// @brief Remove a collider from the physics engine.
        static void RemoveCollider(Collider *collider);
        /// @brief Add a rigidbody to the physics engine.
        static void AddRigidbody(Rigidbody *rigidbody);
        /// @brief Remove a rigidbody from the physics engine.
        static void RemoveRigidbody(Rigidbody *rigidbody);
        /// @brief Update the physics engine.
        static void PhysicsUpdate();

    private:
        static bool sphereToSphereCheck(Collider *collider1, Collider *collider2);
        static void sphereToSphereTrigger(Collider *collider1, Collider *collider2);
        static void sphereToSphereResolution(Collider *collider1, Collider *collider2);
        static bool planeToSphereCheck(Collider *collider1, Collider *collider2);
        static void planeToSphereTrigger(Collider *collider1, Collider *collider2);
        static void planeToSphereResolution(Collider *collider1, Collider *collider2);
        static bool aabbToSphereCheck(Collider *collider1, Collider *collider2);
        static void aabbToSphereTrigger(Collider *collider1, Collider *collider2);
        static void aabbToSphereResolution(Collider *collider1, Collider *collider2);
        static bool aabbToPlaneCheck(Collider *collider1, Collider *collider2);
        static void aabbToPlaneTrigger(Collider *collider1, Collider *collider2);
        static void aabbToPlaneResolution(Collider *collider1, Collider *collider2);
        static bool aabbToAABBCheck(Collider *collider1, Collider *collider2);
        static void aabbToAABBTrigger(Collider *collider1, Collider *collider2);
        static void aabbToAABBResolution(Collider *collider1, Collider *collider2);
    };
}
