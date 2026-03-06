#include "panels/hierarchypanel.h"
#include "editor.h"
#include <imgui.h>
#include <imgui_internal.h>

void CondorEditor::HierarchyPanel::OnGui() {
    ImGui::Begin(getTitle());

    // panel double click
    if (ImGui::IsWindowHovered() && ImGui::IsMouseDoubleClicked(0)) {
        Editor::Instance()->selectedSceneObject = Application::Instance()->activeScene;
    }

    // drop sceneobjects to window
    ImRect rect{
        ImGui::GetWindowPos(),
        ImVec2{ ImGui::GetWindowPos().x + ImGui::GetWindowSize().x,
                ImGui::GetWindowPos().y + ImGui::GetWindowSize().y }
    };
    if (ImGui::BeginDragDropTargetCustom(rect, ImGui::GetID(getTitle()))) {
        std::vector<TypeInfo*> inheritedTypes =
            ReflectionRegistry::GetInheritedTypes(
                TypeResolver<SceneObject>::Get()->name,
                true);
        for (TypeInfo* subType : inheritedTypes) {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(subType->name)) {
                SceneObject* payloadSceneObject = nullptr;

                if (payload->Data != nullptr) {
                    payloadSceneObject = *static_cast<SceneObject* const*>(payload->Data);
                    payloadSceneObject->setParent(nullptr);
                }
                break;
            }
        }
        ImGui::EndDragDropTarget();
    }

    if (Application::Instance()->activeScene != nullptr) {

        for (SceneObject*& obj : Application::Instance()->activeScene->hierarchy) {
            DrawObjectHierarchy(obj);
        }
    }

    ImGui::End();
}

void CondorEditor::HierarchyPanel::DrawObjectHierarchy(SceneObject*& object) {
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_DefaultOpen;

    if (object == Editor::Instance()->selectedSceneObject) {
        flags |= ImGuiTreeNodeFlags_Selected;
    }

    if (object->children.size() <= 0) {
        flags |= ImGuiTreeNodeFlags_Leaf;
    }

    bool opened = ImGui::TreeNodeEx((void*)&object->id, flags, "%s", object->name.c_str());

    // select item
    if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(0)) {
        Editor::Instance()->selectedSceneObject = object;
    }

    // right click context menu
    if (ImGui::BeginPopupContextItem()) {
        if (ImGui::Selectable("Delete")) {
            Scene* scene = object->getScene();
            if (scene != nullptr) {
                object->getScene()->Destroy(object);
            }
            else {
                object->setParent(nullptr);
                if (Editor::Instance()->selectedSceneObject == object) {
                    Editor::Instance()->selectedSceneObject = nullptr;
                }
                delete object;
            }
        }
        ImGui::EndPopup();
    }

    // drag & drop
    DragDropHandler::Source(TypeResolver<SceneObject>::Get()->name, object);
    SceneObject* payloadSceneObject = DragDropHandler::Target<SceneObject>(TypeResolver<SceneObject>::Get()->name);
    if (payloadSceneObject != nullptr) {
        payloadSceneObject->setParent(object);
    }

    if (opened && object->children.size() > 0) {
        for (auto& child : object->children) {
            DrawObjectHierarchy(child);
        }
    }

    if (opened) {
        ImGui::TreePop();
    }
}
