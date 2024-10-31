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

    struct PlaneSize
    {
        Axis axis;
        Vector2 size;
        Vector3 getNormal(Transform transform);
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
        /// @brief Collider dimensions.
        union {
            /// @brief AABB & box collider size.
            Vector3 size;
            /// @brief Sphere collider radius.
            float radius;
            /// @brief Plane collider axis and size.
            PlaneSize plane;
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

