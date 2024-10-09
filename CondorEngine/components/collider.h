#pragma once
#include "../math.h"
#include "../core.h"

namespace CondorEngine
{
    enum ColliderType
    {
        Sphere,
        Box,
        Capsule
    };

    class Collider : public Component
    {
    public:
        Collider();
        ~Collider();
        float radius;
    private:
        ColliderType type;
    public:
        ColliderType getType();
    };
}

