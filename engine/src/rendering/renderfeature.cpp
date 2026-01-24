#include "CondorEngine/rendering/renderfeature.h"
#include "CondorEngine/application.h"

CondorEngine::Rendering::RenderFeature::RenderFeature() {}

void CondorEngine::Rendering::RenderFeature::PostProcess() {
    Vector2Int window = Application::Instance()->getWindowDimensions();
    glViewport(0, 0, window.x, window.y);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void CondorEngine::Rendering::RenderFeature::Render() {
    Vector2Int window = Application::Instance()->getWindowDimensions();
    glViewport(0, 0, window.x, window.y);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void CondorEngine::Rendering::RenderFeature::PreProccess() {
    Vector2Int window = Application::Instance()->getWindowDimensions();
    glViewport(0, 0, window.x, window.y);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
