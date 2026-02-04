#include "CondorEngine/rendering/renderfeatures/imguirenderfeature.h"

CondorEngine::Rendering::ImGuiRenderFeature::ImGuiRenderFeature() {}

void CondorEngine::Rendering::ImGuiRenderFeature::Render() {
    RenderFeature::Render();

    // ImGui frame reset
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void CondorEngine::Rendering::ImGuiRenderFeature::RootDockspace() {
    ImGuiWindowFlags windowFlags =
        ImGuiWindowFlags_NoDocking |
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoNavFocus;

    const ImGuiViewport* viewport = ImGui::GetMainViewport();

    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);

    //ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    //ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    //ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.1f, 0.1f));

    ImGuiDockNodeFlags dockspaceFlags =
        ImGuiDockNodeFlags_PassthruCentralNode |
        ImGuiDockNodeFlags_NoDockingInCentralNode;

    ImGui::Begin("EditorRoot", nullptr, windowFlags);

    ImGuiID dockspaceID = ImGui::GetID(rootDockspace);
    ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), dockspaceFlags);
    ImGui::End();
}

void CondorEngine::Rendering::ImGuiRenderFeature::PostProcess() {
    RenderFeature::Render();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}