#include "collider.h"
//internal
#include "../physics.h"

CondorEngine::Collider::Collider(CondorEngine::ColliderType t) : CondorEngine::Component()
{
    this->name = "CondorEngine::Collider";
    this->type = t;
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
