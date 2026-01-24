#include "CondorEngine/scene.h"
// internal
#include "CondorEngine/debug.hpp"
// std
#include <string>

CondorEngine::Scene::Scene()
{
    this->name = "CondorEngine::Scene";
    hasDoneFirstUpdate = false;
    light = DirectionalLight(ColorRGB{ 1, 1, 1 }, Vector3{ 0, 0, -1 });
}

CondorEngine::Scene::~Scene()
{
    for (int i = 0; i < hierarchy.size(); i++)
    {
        delete hierarchy[i];
    }
}

void CondorEngine::Scene::HierarchyUpdate()
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

    for (int i = 0; i < hierarchy.size(); i++)
    {
        try
        {
            if (hierarchy[i]->enabled)
            {
                hierarchy[i]->HierarchyUpdate();
            }
        }
        catch (const char* msg)
        {
            Debug::LogError(msg);
        }
    }
}

void CondorEngine::Scene::HierarchyFixedUpdate()
{
    if (!enabled || !hasDoneFirstUpdate)
    {
        return;
    }
    FixedUpdate();

    for (int i = 0; i < hierarchy.size(); i++)
    {
        try
        {
            if (hierarchy[i]->enabled)
            {
                hierarchy[i]->HierarchyFixedUpdate();
            }
        }
        catch (const char* msg)
        {
            Debug::LogError(msg);
        }
    }
}

void CondorEngine::Scene::HierarchyLateUpdate()
{
    if (!enabled || !hasDoneFirstUpdate)
    {
        return;
    }

    // delete marked SceneObjects
    for (int i = 0; i < markedDelete.size(); i++)
    {
        RemoveSceneObject(markedDelete[i]);
        delete markedDelete[i];
    }
    markedDelete.clear();

    // late update
    LateUpdate();

    for (int i = 0; i < hierarchy.size(); i++)
    {
        try
        {
            if (hierarchy[i]->enabled)
            {
                hierarchy[i]->HierarchyLateUpdate();
            }
        }
        catch (const char* msg)
        {
            Debug::LogError(msg);
        }
    }
}