#include "editor.h"
#include "editorpanel.h"
#include "panels/consolepanel.hpp"
#include "panels/hierarchypanel.hpp"
#include "panels/inspectorpanel.hpp"
#include "panels/scenepanel.hpp"
#include <imgui.h>
#include <imgui_internal.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

CondorEditor::Editor* CondorEditor::Editor::instance = nullptr;

CondorEditor::Editor::Editor() {
    panels = std::vector<EditorPanel*>();
    sceneCamera = nullptr;
    selectedSceneObject = nullptr;


    playMode = false;
}

CondorEditor::Editor::~Editor() {
    if (instance == this) { instance = nullptr; }
}

CondorEditor::Editor* CondorEditor::Editor::Instance() {
    if (instance == nullptr) {
        instance = new Editor();
    }
    return instance;
}

void CondorEditor::Editor::init() {
    // panels
    panels = std::vector<EditorPanel*>{ new HierarchyPanel(), new InspectorPanel(), new ScenePanel(), new ConsolePanel() };

    // scene camera
    sceneCamera = new Camera();
    if (Camera::Main() == sceneCamera) {
        Camera::SetMainCamera(nullptr);
    }
}

void CondorEditor::Editor::terminate() {
}

void CondorEditor::Editor::BuildDefaultDockLayout(ImGuiID dockspaceId) {
    ImGui::DockBuilderRemoveNode(dockspaceId);
    ImGui::DockBuilderAddNode(
        dockspaceId,
        ImGuiDockNodeFlags_DockSpace
    );
    ImGui::DockBuilderSetNodeSize(
        dockspaceId,
        ImGui::GetMainViewport()->WorkSize
    );

    ImGuiID dockMain = dockspaceId;
    ImGuiID dockLeft, dockRight, dockBottom;

    ImGui::DockBuilderSplitNode(
        dockMain, ImGuiDir_Left, 0.20f, &dockLeft, &dockMain
    );
    ImGui::DockBuilderSplitNode(
        dockMain, ImGuiDir_Right, 0.25f, &dockRight, &dockMain
    );
    ImGui::DockBuilderSplitNode(
        dockMain, ImGuiDir_Down, 0.30f, &dockBottom, &dockMain
    );

    ImGui::DockBuilderDockWindow("Hierarchy", dockLeft);
    ImGui::DockBuilderDockWindow("Inspector", dockRight);
    ImGui::DockBuilderDockWindow("Console", dockBottom);
    ImGui::DockBuilderDockWindow(ScenePanel::getScenePanelName().c_str(), dockMain);

    ImGui::DockBuilderFinish(dockspaceId);
}
