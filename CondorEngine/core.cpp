#include "core.h"

#pragma region Scene

CondorEngine::Scene::Scene()
{
}

CondorEngine::Scene::~Scene()
{
    for (int i = 0; i < hiearchy.size(); i++) {
        delete hiearchy[i];
    }
}

CondorEngine::SceneObject* CondorEngine::Scene::Instanciate(CondorEngine::SceneObject* sceneObject)
{
    sceneObject->setScene(this);
    return sceneObject;
}

#pragma endregion

#pragma region SceneObject

CondorEngine::SceneObject::SceneObject()
{
}

CondorEngine::SceneObject::SceneObject()
{
}

CondorEngine::SceneObject::~SceneObject()
{
    for (int i = 0; i < children.size(); i++) {
        delete children[i];
    }
    for (int i = 0; i < components.size(); i++) {
        delete components[i];
    }
}

void CondorEngine::SceneObject::InternalUpdate()
{
    if (hasDoneFirstUpdate) {
        Start();
    } 
    Update();

    for (int i = 0; i < components.size(); i++) {
        components[i]->InternalUpdate();
    }
    for (int i = 0; i < children.size(); i++) {
        components[i]->InternalUpdate();
    }
}

void CondorEngine::SceneObject::InternalLateUpdate()
{
    LateUpdate();

    for (int i = 0; i < components.size(); i++) {
        components[i]->InternalLateUpdate();
    }
    for (int i = 0; i < children.size(); i++) {
        components[i]->InternalLateUpdate();
    }
}

void CondorEngine::SceneObject::setScene(Scene* scene)
{
    this->scene = scene;
}

CondorEngine::Scene* CondorEngine::SceneObject::getScene()
{
    return scene;
}

CondorEngine::Component* CondorEngine::SceneObject::AddComponent(Component* component)
{
    components.push_back(component);
    return component;
}

#pragma endregion

#pragma region Component

CondorEngine::Component::Component(SceneObject* owner)
{
    this->sceneObject = owner;
}

void CondorEngine::Component::InternalUpdate()
{
    if (!hasDoneFirstUpdate) {
        Start();
    }
    Update();
}

void CondorEngine::Component::InternalLateUpdate()
{
    LateUpdate();
}

CondorEngine::SceneObject* CondorEngine::Component::getSceneObject()
{
    return this->sceneObject;
}

#pragma endregion


