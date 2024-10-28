#include "scene.h"
// internal
#include "debug.hpp"
#include "renderer.h"
// std
#include <string>

CondorEngine::Scene::Scene()
{
    this->name = "CondorEngine::Scene";
    hasDoneFirstUpdate = false;
    light = new DirectionalLight{ ColorRGB{ 1,1,1 }, Vector3{ 0,0,-1 } };
    sceneLights = std::vector<Light*>();
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
        try {
            if (hierarchy[i]->enabled) {
                hierarchy[i]->HierarchyUpdate();
            }
        }
        catch (std::string msg) {
            Debug::LogError(msg);
        } 
        catch (...) {
            Debug::LogError("Failed SceneObject Update : Failed to update SceneObject in Scene(" + name + ") at hierarchy index[" + std::to_string(i) + "].");
        }
    }
}

void CondorEngine::Scene::HierarchyFixedUpdate()
{
    if (!enabled || !hasDoneFirstUpdate) { return; }
    FixedUpdate();

    for (int i = 0; i < hierarchy.size(); i++) {
        try {
            if (hierarchy[i]->enabled) {
                hierarchy[i]->HierarchyFixedUpdate();
            }
        }
        catch (std::string msg) {
            Debug::LogError(msg);
        } 
        catch (...) {
            Debug::LogError("Failed SceneObject FixedUpdate : Failed to fixed update SceneObject in Scene(" + name + ") at hierarchy index[" + std::to_string(i) + "].");
        }
    }
}

void CondorEngine::Scene::HierarchyLateUpdate()
{
    if (!enabled || !hasDoneFirstUpdate) { return; }

    // delete marked SceneObjects
    for (int i = 0; i < markedDelete.size(); i++) {
        RemoveSceneObject(markedDelete[i]);
        delete markedDelete[i];
    }
    markedDelete.clear();
    
    // late update
    LateUpdate();

    for (int i = 0; i < hierarchy.size(); i++) {
        try {
            if (hierarchy[i]->enabled) {
                hierarchy[i]->HierarchyLateUpdate();
            }
        } 
        catch (std::string msg) {
            Debug::LogError(msg);
        } 
        catch (...) {
            Debug::LogError("Failed SceneObject LateUpdate : Failed to late update SceneObject in Scene(" + name + ") at hierarchy index[" + std::to_string(i) + "].");
        }
    }
}