#include "CondorEngine/component.h"
// internal
#include "CondorEngine/physics.h"

CondorEngine::Component::Component()
{
    this->name = "CondorEngine::Component";
    this->sceneObject = nullptr;
    this->hasDoneFirstUpdate = false;
}

void CondorEngine::Component::HierarchyUpdate()
{
    if (!enabled)
    {
        return;
    }
    if (!hasDoneFirstUpdate)
    {
        hasDoneFirstUpdate = true;
        Start();
    }
    Update();
}

void CondorEngine::Component::HierarchyFixedUpdate()
{
    if (!enabled || !hasDoneFirstUpdate)
    {
        return;
    }
    FixedUpdate();
}

void CondorEngine::Component::OnCollision(Collision collision)
{
}

void CondorEngine::Component::HierarchyLateUpdate()
{
    if (!enabled || !hasDoneFirstUpdate)
    {
        return;
    }
    LateUpdate();
}

CondorEngine::SceneObject *CondorEngine::Component::getSceneObject()
{
    return this->sceneObject;
}