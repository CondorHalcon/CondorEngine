#include "scenelight.h"

CondorEngine::SceneLight::SceneLight()
{
    this->light = new Light();
}

CondorEngine::SceneLight::SceneLight(ColorRGB lightColor) : CondorEngine::SceneLight::SceneLight()
{
    this->light->color = lightColor;
}

CondorEngine::SceneLight::SceneLight(ColorRGB lightColor, Vector3 lightDirection) : CondorEngine::SceneLight::SceneLight(lightColor)
{
    this->light->direction = lightDirection;
}
