#include "rigidbody.h"

CondorEngine::Rigidbody::Rigidbody()
{
    this->useGravity = true;
    this->velocity = Vector3{0, 0, 0};
}

void CondorEngine::Rigidbody::FixedUpdate()
{
    
}

void CondorEngine::Rigidbody::AddForce(Vector3 force)
{

}

void CondorEngine::Rigidbody::OnCollision()
{

}