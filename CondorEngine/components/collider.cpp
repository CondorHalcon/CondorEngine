#include "collider.h"
#include "../physics.h"

CondorEngine::Collider::Collider() : CondorEngine::Component()
{
    this->type = ColliderType::Sphere;
    this->radius = 10;
}

void CondorEngine::Collider::FixedUpdate()
{
    Physics::AddCollider(this);
}

CondorEngine::ColliderType CondorEngine::Collider::getType()
{
    return this->type;
}
