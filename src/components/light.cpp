#include "CondorEngine/components/light.h"
// internal
#include "CondorEngine/application.h"
#include "CondorEngine/rendering/renderer.h"
#include "CondorEngine/math.hpp"

CondorEngine::Light::Light(ColorRGB col, Vector3 dir, float cut) {
    this->name = "CondorEngine::Light";
    this->color = col;
    this->direction = dir;
    this->range = 10;
    this->intensity = 1;
    this->cutoff = cut;
    this->outerCutoff = cut;
}

void CondorEngine::Light::LateUpdate() {
    if (enabled) {
        Rendering::Renderer::lights.push_back(this);
    }
}

CondorEngine::ColorRGB CondorEngine::Light::getLightColor()
{
    return color * intensity;
}

CondorEngine::Vector3 CondorEngine::Light::getLightDirection()
{
    return direction;
}

CondorEngine::Vector3 CondorEngine::Light::getLightPosition()
{
    return getSceneObject() != nullptr ? getSceneObject()->getPosition() : Vector3{0, 0, 0};
}

float CondorEngine::Light::getLightCutoff() {
    return glm::cos(glm::radians(cutoff > 180 ? 180 : cutoff));
}

float CondorEngine::Light::getLightOuterCutoff() {
    return outerCutoff <= cutoff ? getLightCutoff() : glm::cos(glm::radians(outerCutoff > 180 ? 180 : outerCutoff));
}
