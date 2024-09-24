#include "core.h"
#include "math.h"
#include "renderer.h"
#include "debug.h"
#include "application.h"
// std
#include <string>

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
    this->hasDoneFirstUpdate = false;
    this->light = new DirectionalLight{ ColorRGB{ 1,1,1 }, Vector3{ 0,0,-1 } };
    this->hierarchy = std::vector<SceneObject*>();
    this->canvases = std::vector<Canvas *>();
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
    // update self
    Update();

    // update SceneObject hierarchy
    for (int i = 0; i < hierarchy.size(); i++) {
        try {
            if (hierarchy[i]->enabled) {
                hierarchy[i]->HierarchyUpdate();
            }
        } catch (...) {
            Debug::LogError("Failed SceneObject Update : Failed to update SceneObject in Scene(" + name + ") at hierarchy index[" + std::to_string(i) + "].");
        }
    }
    // update GUI
    for (int i = 0; i < canvases.size(); i++) {
        try {
            if (canvases[i]->enabled) {
                canvases[i]->HierarchyUpdate();
            }
        } catch (...) {
            Debug::LogError("Failed Canvas Update : Failed to update Canvas in Scene(" + name + ") at index[" + std::to_string(i) + "].");
        }
    }
}

void CondorEngine::Scene::HierarchyLateUpdate()
{
    if (!enabled || !hasDoneFirstUpdate) { return; }
    // late update self
    LateUpdate();

    // late update SceneObject hierarchy
    for (int i = 0; i < hierarchy.size(); i++) {
        try {
            if (hierarchy[i]->enabled) {
                hierarchy[i]->HierarchyLateUpdate();
            }
        } catch (...) {
            Debug::LogError("Failed SceneObject LateUpdate : Failed to late update SceneObject in Scene(" + name + ") at hierarchy index[" + std::to_string(i) + "].");
        }
    }
    // late update GUI Canvases
    for (int i = 0; i < canvases.size(); i++) {
        try {
            if (canvases[i]->enabled) {
                canvases[i]->HierarchyLateUpdate();
            }
        } catch (...) {
            Debug::LogError("Failed Canvas LateUpdate : Failed to late update Canvas in Scene(" + name + ") at index[" + std::to_string(i) + "].");
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
        try {
            components[i]->HierarchyUpdate();
        } catch (...) {
            Debug::LogError("Failed Component Update : Failed to update Component in SceneObject(" + name +  ") at index[" + std::to_string(i) + "].");
        }
    }
    for (int i = 0; i < children.size(); i++) {
        try {
            children[i]->HierarchyUpdate();
        } catch (...) {
            Debug::LogError("Failed Child SceneObject Update : Failed to update child of SceneObject(" + name + ") at child index[" + std::to_string(i) + "].");
        }
    }
}

void CondorEngine::SceneObject::HierarchyLateUpdate()
{
    if (!enabled || !hasDoneFirstUpdate) { return; }
    LateUpdate();

    for (int i = 0; i < components.size(); i++) {
        try {
            components[i]->HierarchyLateUpdate();
        } catch (...) {
            Debug::LogError("Failed Component LateUpdate : Failed to late update Component in SceneObject(" + name +  ") at index[" + std::to_string(i) + "].");
        }
    }
    for (int i = 0; i < children.size(); i++) {
        try {
            children[i]->HierarchyLateUpdate();
        } catch (...) {
            Debug::LogError("Failed Child SceneObject LateUpdate : Failed to late update child of SceneObject(" + name + ") at child index[" + std::to_string(i) + "].");
        }
    }
}

CondorEngine::Scene* CondorEngine::SceneObject::getScene()
{
    return this->scene;
}

void CondorEngine::SceneObject::setScene(Scene* scene)
{
    if (parent != nullptr) {
        throw("Cannot use setScene(Scene*) on a non root SceneObject.");
    }
    this->scene->RemoveSceneObject(this);
    scene->Instantiate(this);
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
    if (newParent != nullptr) {
        newParent->AddChild(this);
    } else {
        Application::activeScene->Instantiate(this);
    }
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
    if (!enabled || !hasDoneFirstUpdate) { return; }
    LateUpdate();
}

CondorEngine::SceneObject* CondorEngine::Component::getSceneObject()
{
    return this->sceneObject;
}

#pragma endregion

#pragma region Canvas

CondorEngine::Canvas::Canvas()
{
    this->hasDoneFirstUpdate = false;
}

CondorEngine::Canvas::~Canvas()
{
}

void CondorEngine::Canvas::HierarchyUpdate()
{
    if (!enabled) { return; }
    if (!hasDoneFirstUpdate) {
        hasDoneFirstUpdate = true;
        Start();
    }
    Update();
}

void CondorEngine::Canvas::HierarchyLateUpdate()
{
    if (!enabled || !hasDoneFirstUpdate) { return; }
    LateUpdate();
}

#pragma endregion
