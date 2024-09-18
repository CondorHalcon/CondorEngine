#include "scenelight.h"

CondorEngine::Light::Light()
{
    this->color = ColorRGB{1, 1, 1};
    this->direction = Vector3 { 0, 0, 0 };
    this->type = LightType::Point;
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

