#include "core.h"
#include "renderer.h"

#pragma region Scene

CondorEngine::Scene::Scene()
{
    hasDoneFirstUpdate = false;
    light = new Light{ glm::vec3{1,1,1}, glm::vec3{0, 0, -1} };
}

CondorEngine::Scene::~Scene()
{
    for (int i = 0; i < hiearchy.size(); i++) {
        delete hiearchy[i];
    }
}

void CondorEngine::Scene::InternalUpdate()
{
    if (!hasDoneFirstUpdate) {
        hasDoneFirstUpdate = true;
        Start();
    }
    Update();

    for (int i = 0; i < hiearchy.size(); i++) {
        hiearchy[i]->InternalUpdate();
    }
}

void CondorEngine::Scene::InternalLateUpdate()
{
    LateUpdate();

    for (int i = 0; i < hiearchy.size(); i++) {
        hiearchy[i]->InternalLateUpdate();
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
    this->scene = nullptr;
    this->transform = glm::identity<mat4>();
    this->components = vector<Component*>();
    this->children = vector<SceneObject*>();
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
    if (!hasDoneFirstUpdate) {
        hasDoneFirstUpdate = true;
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
    component->setSceneObject(this);
    return component;
}

#pragma endregion

#pragma region Component

CondorEngine::Component::Component()
{
    this->sceneObject = nullptr;
    this->hasDoneFirstUpdate = false;
}

void CondorEngine::Component::InternalUpdate()
{
    if (!hasDoneFirstUpdate) {
        hasDoneFirstUpdate = true;
        Start();
    }
    Update();
}

void CondorEngine::Component::InternalLateUpdate()
{
    LateUpdate();
}

void CondorEngine::Component::setSceneObject(SceneObject* sceneObject)
{
    this->sceneObject = sceneObject;
}

CondorEngine::SceneObject* CondorEngine::Component::getSceneObject()
{
    return this->sceneObject;
}

#pragma endregion


