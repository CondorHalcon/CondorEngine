#include "core.h"
#include "renderer.h"


CondorEngine::Object::Object()
{
    this->name = "CondorEngine::Object";
    this->enabled = true;
}

#pragma region Scene

CondorEngine::Scene::Scene()
{
    this->name = "CondorEngine::Scene";
    hasDoneFirstUpdate = false;
    light = new Light{ Vector3{1,1,1}, Vector3{0, 0, -1} };
}

CondorEngine::Scene::~Scene()
{
    for (int i = 0; i < hierarchy.size(); i++) {
        delete hierarchy[i];
    }
}

void CondorEngine::Scene::InternalUpdate()
{
    if (!enabled) { return; }
    if (!hasDoneFirstUpdate) {
        hasDoneFirstUpdate = true;
        Start();
    }
    Update();

    for (int i = 0; i < hierarchy.size(); i++) {
        if (hierarchy[i]->enabled) {
            hierarchy[i]->InternalUpdate();
        }
    }
}

void CondorEngine::Scene::InternalLateUpdate()
{
    if (!enabled) { return; }
    LateUpdate();

    for (int i = 0; i < hierarchy.size(); i++) {
        if (hierarchy[i]->enabled) {
            hierarchy[i]->InternalLateUpdate();
        }
    }
}

#pragma endregion

#pragma region SceneObject

CondorEngine::SceneObject::SceneObject()
{
    this->name = "CondorEngine::SceneObject";
    this->scene = nullptr;
    this->transform = glm::identity<Transform>();
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
    if (!enabled) { return; }
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
    if (!enabled) { return; }
    LateUpdate();

    for (int i = 0; i < components.size(); i++) {
        components[i]->InternalLateUpdate();
    }
    for (int i = 0; i < children.size(); i++) {
        components[i]->InternalLateUpdate();
    }
}

CondorEngine::Scene* CondorEngine::SceneObject::getScene()
{
    return this->scene;
}

void CondorEngine::SceneObject::setScene(Scene* scene)
{
    this->scene = scene;
}

CondorEngine::Transform CondorEngine::SceneObject::getTransform()
{
    return this->transform;
}

void CondorEngine::SceneObject::setTransform(Transform transform)
{
    this->transform = transform;
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
    if (!enabled) { return; }
    if (!hasDoneFirstUpdate) {
        hasDoneFirstUpdate = true;
        Start();
    }
    Update();
}

void CondorEngine::Component::InternalLateUpdate()
{
    if (!enabled) { return; }
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

