#include "collider.h"
#include "../physics.h"

CondorEngine::Collider::Collider() : CondorEngine::Component()
{
    this->name = "CondorEngine::Collider";
    this->type = ColliderType::Sphere;
    this->radius = .5f;
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
