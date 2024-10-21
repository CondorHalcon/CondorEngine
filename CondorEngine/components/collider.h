#pragma once
// internal
#include "../component.h"

namespace CondorEngine
{
    /// @brief Collider type enumeration.
    enum ColliderType
    {
        Sphere,
        Plane,
        Box,
        Capsule
    };

    /// @brief Engine collider component class.
    class Collider : public Component
    {
    public:
        /// @brief Class constructor.
        /// @param type Collider type.
        Collider(ColliderType type);
        /// @brief Class destructor.
        ~Collider();
        /// @brief Collider radius.
        float radius;
        /// @brief Collider height.
        bool isTrigger;
    private:
        /// @brief Collider type.
        ColliderType type;
    public:
        /// @brief Get the collider type.
        ColliderType getType();
    };
}

