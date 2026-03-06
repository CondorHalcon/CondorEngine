#include "editorrenderer.h"
#include "editor.h"
#include "editorpanel.h"
#include "editormainmenubar.h"
#include <imgui.h>
#include <imgui_internal.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

CondorEditor::EditorRenderFeature::EditorRenderFeature() {}

void CondorEditor::EditorRenderFeature::Render() {
    static bool hasDoneFirstDraw = false;

    ImGuiRenderFeature::Render();

    ImGuiID dockspaceId = ImGui::GetID(rootDockspace);
    ImGuiViewport* viewport = ImGui::GetMainViewport();

    if (!hasDoneFirstDraw) {
        BuildDefaultDockLayout(dockspaceId, viewport);
        hasDoneFirstDraw = true;
    }
    
    // Submit dockspace
    ImGui::DockSpaceOverViewport(dockspaceId, viewport, 0);

    EditorMainMenuBar::Instance()->DrawMainMenuBar();

    for (EditorPanel* panel : Editor::Instance()->panels) {
        panel->OnGui();
    }
}

void CondorEditor::EditorRenderFeature::BuildDefaultDockLayout(ImGuiID dockspaceId, ImGuiViewport* viewport) {

    if (ImGui::DockBuilderGetNode(dockspaceId) == nullptr) {
        ImGui::DockBuilderAddNode(dockspaceId, ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(dockspaceId, viewport->WorkSize);

        ImGuiID dockMain = dockspaceId;
        ImGuiID dockLeft, dockRight, dockBottom;

        ImGui::DockBuilderSplitNode(dockMain, ImGuiDir_Right, 0.2f, &dockRight, &dockMain);
        ImGui::DockBuilderSplitNode(dockMain, ImGuiDir_Down, 0.25f, &dockBottom, &dockMain);
        ImGui::DockBuilderSplitNode(dockMain, ImGuiDir_Left, 0.25f, &dockLeft, &dockMain);

        ImGui::DockBuilderDockWindow("Scene", dockMain);
        ImGui::DockBuilderDockWindow("Hierarchy", dockLeft);
        ImGui::DockBuilderDockWindow("Console", dockBottom);
        ImGui::DockBuilderDockWindow("Project", dockBottom);
        ImGui::DockBuilderDockWindow("Inspector", dockRight);

        ImGui::DockBuilderFinish(dockspaceId);
    }
}

CondorEditor::EditorRenderer::EditorRenderer() {}

void CondorEditor::EditorRenderer::init() {
    Renderer::init();

    // initialize render features
    features = std::vector<RenderFeature*>{
        //DirectionalShadowMappingRenderFeature::Instance(),
        //SceneViewRenderFeature::Instance(),
        new EditorRenderFeature() };

    // Create GL resources for the scene framebuffer now that the GL context
    /*SceneViewRenderFeature* sceneFeature = SceneViewRenderFeature::Instance();
    if (sceneFeature) {
        sceneFeature->CreateSceneFramebuffer(sceneFeature->sceneSize.x, sceneFeature->sceneSize.y);
    }*/
}
