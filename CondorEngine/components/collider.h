#pragma once
// internal
#include "../component.h"

namespace CondorEngine
{
    enum ColliderType
    {
        Sphere,
        Plane,
        Box,
        Capsule
    };

    class Collider : public Component
    {
    public:
        Collider(ColliderType type);
        ~Collider();
        float radius;
    private:
        ColliderType type;
    public:
        ColliderType getType();
    };
}

