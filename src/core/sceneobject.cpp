#include "CondorEngine/sceneobject.h"
// internal
#include "CondorEngine/debug.hpp"
#include "CondorEngine/application.h"
#include "CondorEngine/physics.h"
#include "CondorEngine/scene.h"
#include "CondorEngine/component.h"
#include "CondorEngine/components/collider.h"

CondorEngine::SceneObject::SceneObject()
{
    this->name = "CondorEngine::SceneObject";
    this->scene = nullptr;
    this->transform = glm::identity<Transform>();
    this->components = std::vector<Component *>();
    this->children = std::vector<SceneObject *>();
    this->parent = nullptr;
}

CondorEngine::SceneObject::~SceneObject()
{
    for (int i = 0; i < children.size(); i++)
    {
        delete children[i];
    }
    for (int i = 0; i < components.size(); i++)
    {
        delete components[i];
    }
}

void CondorEngine::SceneObject::HierarchyUpdate()
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

    for (int i = 0; i < components.size(); i++)
    {
        try
        {
            components[i]->HierarchyUpdate();
        }
        catch (const char* msg)
        {
            Debug::LogError(msg);
        }
    }
    for (int i = 0; i < children.size(); i++)
    {
        try
        {
            children[i]->HierarchyUpdate();
        }
        catch (const char* msg)
        {
            Debug::LogError(msg);
        }
    }
}

void CondorEngine::SceneObject::HierarchyFixedUpdate()
{
    if (!enabled || !hasDoneFirstUpdate)
    {
        return;
    }
    FixedUpdate();

    for (int i = 0; i < components.size(); i++)
    {
        try
        {
            components[i]->HierarchyFixedUpdate();
        }
        catch (const char* msg)
        {
            Debug::LogError(msg);
        }
    }
    for (int i = 0; i < children.size(); i++)
    {
        try
        {
            children[i]->HierarchyFixedUpdate();
        }
        catch (const char* msg)
        {
            Debug::LogError(msg);
        }
    }
}

void CondorEngine::SceneObject::HierarchyLateUpdate()
{
    if (!enabled || !hasDoneFirstUpdate)
    {
        return;
    }
    LateUpdate();

    for (int i = 0; i < components.size(); i++)
    {
        try
        {
            components[i]->HierarchyLateUpdate();
        }
        catch (const char* msg)
        {
            Debug::LogError(msg);
        }
    }
    for (int i = 0; i < children.size(); i++)
    {
        try
        {
            children[i]->HierarchyLateUpdate();
        }
        catch (const char* msg)
        {
            Debug::LogError(msg);
        }
    }
}

void CondorEngine::SceneObject::ObjectOnCollision(Collision collision)
{
    OnCollision(collision);
    for (int i = 0; i < components.size(); i++)
    {
        components[i]->OnCollision(collision);
    }
}

void CondorEngine::SceneObject::OnCollision(Collision collision)
{
}

#pragma region Getters and Setters

CondorEngine::Scene *CondorEngine::SceneObject::getScene()
{
    return this->scene;
}

void CondorEngine::SceneObject::setScene(Scene *scene)
{
    if (parent != nullptr)
    {
        throw("CondorEngine::SceneObject :: Cannot use setScene(Scene*) on a non root SceneObject.");
    }
    this->scene->RemoveSceneObject(this);
    scene->Instantiate(this);
}

CondorEngine::SceneObject *CondorEngine::SceneObject::getParent()
{
    return parent;
}

void CondorEngine::SceneObject::setParent(SceneObject *newParent)
{
    if (parent != nullptr)
    {
        parent->RemoveChild(this);
    }
    if (newParent != nullptr)
    {
        newParent->AddChild(this);
    }
    else
    {
        Application::activeScene->Instantiate(this);
    }
}

CondorEngine::SceneObject *CondorEngine::SceneObject::getRoot()
{
    return parent == nullptr ? this : parent->getRoot();
}

bool CondorEngine::SceneObject::isRoot()
{
    return parent == nullptr;
}

unsigned int CondorEngine::SceneObject::getChildCount()
{
    return this->children.size();
}

CondorEngine::Vector3 CondorEngine::SceneObject::getForward()
{
    return getTransform()[2];
}

CondorEngine::Vector3 CondorEngine::SceneObject::getRight()
{
    return getTransform()[0];
}

CondorEngine::Vector3 CondorEngine::SceneObject::getUp()
{
    return getTransform()[1];
}

CondorEngine::Transform CondorEngine::SceneObject::getTransform()
{
    return parent != nullptr ? parent->getTransform() * transform : transform;
}

CondorEngine::Transform CondorEngine::SceneObject::getLocalTransform()
{
    return transform;
}

CondorEngine::Vector3 CondorEngine::SceneObject::getPosition()
{
    return Vector3{getTransform()[3]};
}

void CondorEngine::SceneObject::setPosition(Vector3 position)
{
    Vector3 pos = parent != nullptr ? position - parent->getPosition() : position;
    setLocalPosition(pos);
}

CondorEngine::Vector3 CondorEngine::SceneObject::getLocalPosition()
{
    return Vector3{transform[3]};
}

void CondorEngine::SceneObject::setLocalPosition(Vector3 position)
{
    transform[3] = Vector4(position, transform[3].w);
}

CondorEngine::Quaternion CondorEngine::SceneObject::getRotation()
{
    return glm::quat_cast(getTransform());
}

CondorEngine::Quaternion CondorEngine::SceneObject::getLocalRotation()
{
    return glm::quat_cast(transform);
}

void CondorEngine::SceneObject::setRotation(Quaternion rotation)
{
    Quaternion rot;
    if (parent != nullptr)
    {
        rot = glm::inverse(glm::quat_cast(parent->getTransform())) * rotation;
    }
    else
    {
        rot = rotation;
    }
    setLocalRotation(rot);
}

void CondorEngine::SceneObject::setLocalRotation(Quaternion rotation)
{
    Transform t = glm::mat4_cast(rotation);
    t = glm::scale(t, getLocalScale());
    t[3] = transform[3];
    transform = t;
}

CondorEngine::Vector3 CondorEngine::SceneObject::getScale()
{
    Transform t = getTransform();
    return Vector3{
        glm::length(Vector3{t[0]}),
        glm::length(Vector3{t[1]}),
        glm::length(Vector3{t[2]})};
}

CondorEngine::Vector3 CondorEngine::SceneObject::getLocalScale()
{
    return Vector3{
        glm::length(Vector3{transform[0]}),
        glm::length(Vector3{transform[1]}),
        glm::length(Vector3{transform[2]})};
}

std::vector<std::string> CondorEngine::SceneObject::getLayerNames() {
    return Application::GetLayers(layer);
}

#pragma endregion

#pragma region Transformation

void CondorEngine::SceneObject::Move(Vector3 vector, bool worldSpace)
{
    if (worldSpace)
    {
        transform[3] = getTransform()[3] + Vector4(vector, 0);
    }
    else
    {
        transform[3] += Vector4(vector, 0);
    }
}

void CondorEngine::SceneObject::Rotate(Vector3 vector, bool worldSpace)
{
    transform = glm::rotate(
        worldSpace ? getTransform() : transform,
        glm::radians(glm::length(vector)),
        glm::normalize(vector));
}

void CondorEngine::SceneObject::Scale(Vector3 scaler)
{
    transform = glm::scale(transform, scaler);
}

#pragma endregion
