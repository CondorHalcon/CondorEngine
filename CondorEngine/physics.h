#pragma once
#include "core.h"
#include "math.h"
#include "components/rigidbody.h"
#include "components/collider.h"
// std
#include <vector>

namespace CondorEngine
{
    class Physics
    {
    public:
        static void init();
    private:
        static std::vector<Collider*> colliders;
        static std::vector<Rigidbody*> rigidbodies;
    public:
        static void AddCollider(Collider* collider);
        static void AddRigidbody(Rigidbody* rigidbody);
        static void PhysicsUpdate();
    };
}
