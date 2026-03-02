#include "CondorEngine/rendering/renderfeatures/imguirenderfeature.h"

CondorEngine::Rendering::ImGuiRenderFeature::ImGuiRenderFeature() {}

void CondorEngine::Rendering::ImGuiRenderFeature::Render() {
    RenderFeature::Render();

    // ImGui frame reset
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void CondorEngine::Rendering::ImGuiRenderFeature::PostProcess() {
    RenderFeature::Render();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}