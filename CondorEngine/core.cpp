#include "core.h"
#include "math.h"
#include "renderer.h"
#include "debug.h"

#pragma region Object

CondorEngine::Object::Object()
{
    this->name = "CondorEngine::Object";
    this->enabled = true;
}

#pragma endregion

#pragma region Scene

CondorEngine::Scene::Scene()
{
    this->name = "CondorEngine::Scene";
    hasDoneFirstUpdate = false;
    light = new DirectionalLight{ ColorRGB{ 1,1,1 }, Vector3{ 0,0,-1 } };
}

CondorEngine::Scene::~Scene()
{
    for (int i = 0; i < hierarchy.size(); i++) {
        delete hierarchy[i];
    }
}

void CondorEngine::Scene::HierarchyUpdate()
{
    if (!enabled) { return; }
    if (!hasDoneFirstUpdate) {
        hasDoneFirstUpdate = true;
        Start();
    }
    Update();

    for (int i = 0; i < hierarchy.size(); i++) {
        if (hierarchy[i]->enabled) {
            hierarchy[i]->HierarchyUpdate();
        }
    }
}

void CondorEngine::Scene::HierarchyLateUpdate()
{
    if (!enabled) { return; }
    LateUpdate();

    for (int i = 0; i < hierarchy.size(); i++) {
        if (hierarchy[i]->enabled) {
            hierarchy[i]->HierarchyLateUpdate();
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
    this->position = Vector3{ 0,0,0 };
    this->rotation = Vector3{ 0,0,0 };
    this->scale = Vector3{ 1,1,1 };
    this->components = vector<Component*>();
    this->children = vector<SceneObject*>();
    this->parent = nullptr;
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

void CondorEngine::SceneObject::HierarchyUpdate()
{
    if (!enabled) { return; }
    if (!hasDoneFirstUpdate) {
        hasDoneFirstUpdate = true;
        Start();
    } 
    Update();

    for (int i = 0; i < components.size(); i++) {
        components[i]->HierarchyUpdate();
    }
    for (int i = 0; i < children.size(); i++) {
        components[i]->HierarchyUpdate();
    }
}

void CondorEngine::SceneObject::HierarchyLateUpdate()
{
    if (!enabled) { return; }
    LateUpdate();

    for (int i = 0; i < components.size(); i++) {
        components[i]->HierarchyLateUpdate();
    }
    for (int i = 0; i < children.size(); i++) {
        components[i]->HierarchyLateUpdate();
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

CondorEngine::SceneObject* CondorEngine::SceneObject::getParent()
{
    return parent;
}

void CondorEngine::SceneObject::setParent(SceneObject* newParent)
{
    if (parent != nullptr) {
        parent->RemoveChild(this);
    }
    newParent->AddChild(this);
}

CondorEngine::SceneObject* CondorEngine::SceneObject::getRoot()
{
    return parent == nullptr ? this : parent->getRoot();
}

bool CondorEngine::SceneObject::isRoot()
{
    return parent == nullptr;
}

CondorEngine::Vector3 CondorEngine::SceneObject::getForward()
{
    return Math::TransformForward(getTransform());
}

CondorEngine::Vector3 CondorEngine::SceneObject::getRight()
{
    return Math::TransformRight(getTransform());
}

CondorEngine::Vector3 CondorEngine::SceneObject::getUp()
{
    return Math::TransformUp(getTransform());
}

CondorEngine::Transform CondorEngine::SceneObject::getTransform()
{
    return parent != nullptr ? parent->getTransform() * getLocalTransform() : getLocalTransform();
}

CondorEngine::Transform CondorEngine::SceneObject::getLocalTransform()
{
    /*
    Transform t = glm::scale(glm::identity<Transform>(), this->scale);
    t = glm::rotate(t, glm::radians(glm::length(this->rotation)), glm::normalize(this->rotation));
    t = glm::translate(t, this->position);*/
    return transform;
}

CondorEngine::Vector3 CondorEngine::SceneObject::getPosition()
{
    Vector3 pos;
    Quaternion rot;
    Vector3 scale;
    Math::TransformSplit(getTransform(), pos, rot, scale);
    return pos;
}

CondorEngine::Vector3 CondorEngine::SceneObject::getLocalPosition()
{
    Vector3 pos;
    Quaternion rot;
    Vector3 scale;
    Math::TransformSplit(getLocalTransform(), pos, rot, scale);
    return pos;
}

void CondorEngine::SceneObject::Move(Vector3 vector)
{
    transform = glm::translate(transform, vector);
    position += vector;
}

void CondorEngine::SceneObject::Rotate(Vector3 vector) {
    transform = glm::rotate(transform, glm::radians(glm::length(vector)), glm::normalize(vector));
    rotation += vector;
}
#pragma endregion

#pragma region Component

CondorEngine::Component::Component()
{
    this->name = "CondorEngine::Component";
    this->sceneObject = nullptr;
    this->hasDoneFirstUpdate = false;
}

void CondorEngine::Component::HierarchyUpdate()
{
    if (!enabled) { return; }
    if (!hasDoneFirstUpdate) {
        hasDoneFirstUpdate = true;
        Start();
    }
    Update();
}

void CondorEngine::Component::HierarchyLateUpdate()
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

