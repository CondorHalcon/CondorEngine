#include "editor.h"
#include "editorpanel.h"
#include "panels.hpp"
#include "editorscenecamera.hpp"
#include <imgui.h>

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
	ImGui::SetCurrentContext(Application::Instance()->imguiContext);

    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = "EditorConfig.ini";

    // panels
    panels = std::vector<EditorPanel*>{ HierarchyPanel::Instance(), InspectorPanel::Instance(), ScenePanel::Instance(), ProjectPanel::Instance(), ConsolePanel::Instance() };

    // scene camera
    if (!sceneCamera) {
        sceneCamera = new EditorSceneCamera();
        sceneCamera->Move(Vector3{ 0, 5, -5 });
        sceneCamera->Rotate(Vector3{ 0, 35, 0 });
    }
}

void CondorEditor::Editor::terminate() {
}

void CondorEditor::Editor::AddPanel(EditorPanel* panel) {
    for (EditorPanel* existingPanel : panels) {
        if (panel == existingPanel) {
            return; // already in registered panels
        }
    }

    panels.push_back(panel);
}

bool CondorEditor::Editor::RemovePanel(EditorPanel* panel, bool destroy) {
    for (int i = 0; i < panels.size(); i++) {
        if (panels[i] == panel) {
            panels.erase(std::next(panels.begin(), i));
            if (destroy) {
                delete panel;
            }
            return true;
        }
    }

    return false;
}
