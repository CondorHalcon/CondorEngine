#pragma once
// internal
#include "../math.h"
#include "../component.h"

namespace CondorEngine
{
    /// @brief Collider type enumeration.
    enum ColliderType
    {
        Sphere = 1,
        Plane = 2,
        AABB = 4,
        Capsule = 8
    };

    /// @brief Collider component class.
    class Collider : public Component
    {
    public:
        /// @brief Class constructor.
        /// @param type Collider type.
        Collider(ColliderType type);
        /// @brief Class destructor.
        ~Collider();
        /// @brief Collider size or radius.
        union {
            /// @brief Collider size.
            Vector3 size;
            /// @brief Collider radius.
            float radius;
        };
        /// @brief Collider height.
        bool isTrigger;
    private:
        /// @brief Collider type.
        ColliderType type;
    public:
        /// @brief Get the collider type.
        ColliderType getType();
        /// @brief Get the closest point on the collider to a given point.
        /// @param point The reference point.
        /// @return Point on the collider.
        Vector3 getClosestPoint(Vector3 point);
    };
}

