#include "editormainmenubar.h"
#include "editor.h"
#include <CondorEngine/serialization.hpp>

CondorEditor::EditorMainMenuBar::EditorMainMenuBar() {}

CondorEditor::EditorMainMenuBar::~EditorMainMenuBar() {
    if (instance == this) { instance = nullptr; }
}

CondorEditor::EditorMainMenuBar* CondorEditor::EditorMainMenuBar::Instance() {
    if (instance == nullptr) {
        instance = new EditorMainMenuBar();
    }
    return instance;
}

void CondorEditor::EditorMainMenuBar::DrawMainMenuBar() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("Project")) {
            ProjectMenu();
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit")) {
            EditMenu();
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Panels")) {
            PanelsMenu();
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Plugins")) {
            PluginsMenu();
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}

void CondorEditor::EditorMainMenuBar::ProjectMenu() {
    if (ImGui::MenuItem("New Project")) {}
    if (ImGui::MenuItem("Open Project")) {}
    if (ImGui::MenuItem("Save Project")) {}
    if (ImGui::MenuItem("Close Project")) {}

    ImGui::Separator();
    if (ImGui::MenuItem("Project Settings", "Ctrl+,")) {}
    if (ImGui::MenuItem("Plugin Manager")) {}
    if (ImGui::MenuItem("Build Project", "Ctrl+Print")) {}

    ImGui::Separator();
    if (ImGui::MenuItem("User Settings", "Ctrl+.")) {}
}

void CondorEditor::EditorMainMenuBar::EditMenu() {
    if (ImGui::MenuItem("New Scene", "Ctrl+N")) {}
    if (ImGui::MenuItem("Open Scene", "Ctrl+O")) {}
    if (ImGui::MenuItem("Save Scene", "Ctrl+S")) {}
    if (ImGui::MenuItem("Save Scene As", "Ctrl+Shift+S")) {}

    ImGui::Separator();
    if (ImGui::MenuItem("Undo", "Ctrl+Z")) {}
    if (ImGui::MenuItem("Redo", "Ctrl+Y")) {}

    ImGui::Separator();
    if (ImGui::BeginMenu("New SceneObject")) {
        NewSceneObjectSubMenu();
        ImGui::EndMenu();
    }
}

void CondorEditor::EditorMainMenuBar::PanelsMenu() {
    if (ImGui::MenuItem("Console")) {}
    if (ImGui::MenuItem("Hierarchy")) {}
    if (ImGui::MenuItem("Inspector")) {}
    if (ImGui::MenuItem("Project")) {}
    if (ImGui::MenuItem("Scene")) {}

    ImGui::Separator();
}

void CondorEditor::EditorMainMenuBar::PluginsMenu() {
    if (ImGui::MenuItem("Plugin Manager")) {}

    ImGui::Separator();
}

inline SceneObject* NewSceneObject(TypeInfo* type, Object* selectedObject) {
    if (type == nullptr) {
        Debug::LogError("EditorMainMenuBar :: <type> == nullptr");
        return nullptr;
    }
    if (type->CreateInstance == nullptr) {
        Debug::LogError("EditorMainMenuBar :: <type> has no instancing function.");
        return nullptr;
    }
    if (selectedObject == nullptr) {
        selectedObject = Application::activeScene;
        Debug::LogWarning("EditorMainMenuBar :: No selected object; adding to scene");
    }

    //TODO fix forced cast
    SceneObject* sceneObject = dynamic_cast<SceneObject*>(selectedObject); 
    Scene* scene = dynamic_cast<Scene*>(selectedObject);
    if (sceneObject != nullptr) {
        void* inst = type->CreateInstance();
        SceneObject* child = (SceneObject*)inst;
        sceneObject->AddChild(child);
        return child;
    }
    else if (scene != nullptr) {
        void* inst = type->CreateInstance();
        SceneObject* child = (SceneObject*)inst;
        scene->Instantiate(child);
        return child;
    }

    Debug::LogError("EditorMainMenuBar :: Selected object is not of type <Scene> or <SceneObject>.");
    return nullptr;
}

void CondorEditor::EditorMainMenuBar::NewSceneObjectSubMenu() {
    if (ImGui::MenuItem("SceneObject")) {
        SceneObject* newSceneObject = NewSceneObject(TypeResolver<SceneObject>::Get(), Editor::Instance()->selectedSceneObject);
        if (newSceneObject != nullptr) {
            Editor::Instance()->selectedSceneObject = newSceneObject;
        }
    }

    ImGui::Separator();
    std::vector<TypeInfo*> sceneObjectTypes = ReflectionRegistry::GetInheritedTypes(TypeResolver<SceneObject>::Get()->name, false);
    for (TypeInfo* type : sceneObjectTypes) {
        if (ImGui::MenuItem(type->name)) {
            SceneObject* newSceneObject = NewSceneObject(type, Editor::Instance()->selectedSceneObject);
            if (newSceneObject != nullptr) {
                Editor::Instance()->selectedSceneObject = newSceneObject;
            }
        }
    }
}
