#include "editor.h"
#include "editorpanel.h"
#include "panels/consolepanel.hpp"
#include "panels/hierarchypanel.hpp"
#include "panels/inspectorpanel.hpp"
#include "panels/projectpanel.hpp"
#include "panels/scenepanel.hpp"

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
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = "EditorConfig.ini";

    // panels
    panels = std::vector<EditorPanel*>{ new HierarchyPanel(), new InspectorPanel(), new ScenePanel(), new ProjectPanel(), new ConsolePanel() };

    // scene camera
    sceneCamera = new Camera();
    if (Camera::Main() == sceneCamera) {
        Camera::SetMainCamera(nullptr);
    }
}

void CondorEditor::Editor::terminate() {
}
