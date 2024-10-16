#pragma once
// third party
#include "math.h"
#include "components/rigidbody.h"
#include "components/collider.h"
// std
#include <vector>

namespace CondorEngine
{
    typedef bool(*CollisionCheckFn)(Collider* collider1, Collider* collider2);
    typedef void(*CollisionResolutionFn)(Collider* collider1, Collider* collider2);

    class Physics
    {
    public:
        static void init();
    private:
        static std::vector<Collider*> colliders;
        static std::vector<Rigidbody*> rigidbodies;
    public:
        static void AddCollider(Collider* collider);
        static void RemoveCollider(Collider *collider);
        static void AddRigidbody(Rigidbody* rigidbody);
        static void RemoveRigidbody(Rigidbody *rigidbody);
        static void PhysicsUpdate();
    private:
        static bool sphereToSphereCheck(Collider* collider1, Collider* collider2);
        static void sphereToSphereResolution(Collider* collider1, Collider* collider2);
        static bool sphereToPlaneCheck(Collider* collider1, Collider* collider2);
        static void sphereToPlaneResolution(Collider* collider1, Collider* collider2);
    };
}
