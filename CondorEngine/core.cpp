#include "core.h"
#include "math.h"
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
    light = new DirectionalLight{ Vector3{1,1,1}, Vector3{0, 0, -1} };
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
    return parent != nullptr ? parent->getTransform() * this->transform : this->transform;
}

CondorEngine::Transform CondorEngine::SceneObject::getLocalTransform()
{
    return this->transform;
}

void CondorEngine::SceneObject::setLocalTransform(Transform transform)
{
    this->transform = transform;
}

CondorEngine::Vector3 CondorEngine::SceneObject::getPosition()
{
    Vector3 pos;
    Quaternion rot;
    Vector3 scale;
    Math::TransformSplit(getTransform(), pos, rot, scale);
    return pos;
}

void CondorEngine::SceneObject::setParent(SceneObject* newParent)
{
    if (parent != nullptr) {
        parent->RemoveChild(this);
    }
    newParent->AddChild(this);
}

CondorEngine::SceneObject* CondorEngine::SceneObject::getParent()
{
    return parent;
}

CondorEngine::SceneObject* CondorEngine::SceneObject::getRoot()
{
    return parent == nullptr ? this : parent->getRoot();
}

bool CondorEngine::SceneObject::isRoot()
{
    return parent == nullptr;
}

void CondorEngine::SceneObject::Move(Vector3 vector)
{
    transform = Math::TransformTranslate(transform, vector * Vector3{ -1,1,1 });
}

void CondorEngine::SceneObject::Rotate(Vector3 vector) {
    transform = Math::TransformRotate(transform, vector);
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

