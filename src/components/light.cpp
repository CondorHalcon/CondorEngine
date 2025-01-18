#include "CondorEngine/components/light.h"
// internal
#include "CondorEngine/application.h"

CondorEngine::Light::Light()
{
    this->color = ColorRGB{.5, .5, .5};
    this->direction = Vector3{0, 0, -1};
    this->type = LightType::Point;
    if (Application::activeScene != nullptr)
    {
        Application::activeScene->sceneLights.push_back(this);
    }
}

CondorEngine::Light::~Light()
{
    if (Application::activeScene == nullptr)
    {
        return;
    }

    for (int i = 0; i < Application::activeScene->sceneLights.size(); i++)
    {
        if (Application::activeScene->sceneLights[i] == this)
        {
            Application::activeScene->sceneLights.erase(std::next(Application::activeScene->sceneLights.begin(), i));
        }
    }
}

CondorEngine::ColorRGB CondorEngine::Light::getLightColor()
{
    return color;
}

CondorEngine::Vector3 CondorEngine::Light::getLightDirection()
{
    return direction;
}

CondorEngine::Vector3 CondorEngine::Light::getLightPosition()
{
    return getSceneObject() != nullptr ? getSceneObject()->getPosition() : Vector3{0, 0, 0};
}
