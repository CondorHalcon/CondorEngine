#include "CondorEngine/sceneobjects/scenelight.h"

CondorEngine::SceneLight::SceneLight(ColorRGB lightColor, Vector3 lightDirection, float cutoff) : SceneObject("SceneLight")
{
    this->light = AddComponent<Light>(new Light(lightColor, lightDirection, cutoff));
}
