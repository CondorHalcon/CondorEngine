#include "CondorEngine/components/collider.h"
// internal
#include "CondorEngine/sceneobject.h"
#include "CondorEngine/physics.h"

CondorEngine::Vector3 CondorEngine::PlaneSize::getNormal(Transform transform)
{
    return Math::getTransformAxis(transform, axis);
}

CondorEngine::Collider::Collider(CondorEngine::ColliderType t) : CondorEngine::Component()
{
    this->name = "CondorEngine::Collider";
    this->type = t;
    switch (t)
    {
    case ColliderType::Sphere:
        this->radius = .5f;
        break;
    case ColliderType::Plane:
        this->plane.axis = Axis::Up;
        this->plane.size = Vector2{1, 1};
        break;
    default:
        this->size = Vector3{1, 1, 1};
        break;
    }
    this->isTrigger = false;
    Physics::AddCollider(this);
}

CondorEngine::Collider::~Collider()
{
    Physics::RemoveCollider(this);
}

CondorEngine::ColliderType CondorEngine::Collider::getType()
{
    return this->type;
}

CondorEngine::Vector3 CondorEngine::Collider::getClosestPoint(Vector3 point)
{
    float x = 0;
    float y = 0;
    float z = 0;
    Vector3 offset;
    Vector3 normal;
    float distance;
    switch (this->type)
    {
    case ColliderType::Sphere:
        offset = point - this->getSceneObject()->getPosition();
        normal = glm::normalize(offset);
        return this->getSceneObject()->getPosition() + (normal * this->radius * this->getSceneObject()->getScale());
    case ColliderType::Plane:
        offset = point - this->getSceneObject()->getPosition();
        normal = this->plane.getNormal(this->getSceneObject()->getTransform());
        distance = glm::dot(offset, normal);
        return point - normal * distance;
    case ColliderType::AABB:
        Vector3 halfSize = this->size * .5f * this->getSceneObject()->getScale();
        x = glm::fclamp(point.x,
                        this->getSceneObject()->getPosition().x - halfSize.x,
                        this->getSceneObject()->getPosition().x + halfSize.x);
        y = glm::fclamp(point.y,
                        this->getSceneObject()->getPosition().y - halfSize.y,
                        this->getSceneObject()->getPosition().y + halfSize.y);
        z = glm::fclamp(point.z,
                        this->getSceneObject()->getPosition().z - halfSize.z,
                        this->getSceneObject()->getPosition().z + halfSize.z);
        if (x == point.x || y == point.y || z == point.z)
        {
            // FIXME: clamp to closest face
            // the point is inside the box
            // return this->getClosestPoint(Vector3{x, y, z} * glm::length(this->size));
        }
        return Vector3{x, y, z};
    default:
        return point;
    }
}
