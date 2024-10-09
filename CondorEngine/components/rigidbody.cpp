#include "rigidbody.h"
#include "../physics.h"
#include "glm/ext.hpp"

CondorEngine::Rigidbody::Rigidbody() : CondorEngine::Component()
{
    this->name = "CondorEngine::Rigidbody";
    this->mass = 1.0f;
    this->useGravity = true;
    this->velocity = Vector3{0, 0, 0};
    Physics::AddRigidbody(this);
}

CondorEngine::Rigidbody::~Rigidbody()
{
    Physics::RemoveRigidbody(this);
}

void CondorEngine::Rigidbody::AddForce(Vector3 force)
{
    float inertia = this->mass * glm::length(force);
    this->velocity += glm::normalize(force) * inertia;
}

CondorEngine::Vector3 CondorEngine::Rigidbody::getVelocity()
{
    return this->velocity;
}

void CondorEngine::Rigidbody::setVelocity(Vector3 vel)
{
    this->velocity = vel;
}
