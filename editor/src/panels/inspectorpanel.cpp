#include "panels/inspectorpanel.h"
#include "editor.h"
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include <misc/cpp/imgui_stdlib.cpp>

inline bool CondorEditor::InspectorPanel::isSpecialFieldName(const char* fieldName) {
    for (std::string name : specialFieldNames) {
        if (name == fieldName) { return true; }
    }

    return false;
}

void CondorEditor::InspectorPanel::OnGui() {
    Object* selected = Editor::Instance()->selectedSceneObject;
    ImGui::Begin(getTitle());

    if (selected != nullptr) {
        SceneObject* sceneObject = dynamic_cast<SceneObject*>(selected);
        std::vector<FieldInfo> fields;
        selected->GetTypeInfo()->CollectFields(fields);

        // special fields being used by this function
        FieldInfo* nameField = nullptr;
        FieldInfo* enabledField = nullptr;
        FieldInfo* componentsField = nullptr;
        for (auto& field : fields) {
            if (std::strcmp(field.name, "name") == 0) { nameField = &field; }
            else if (std::strcmp(field.name, "enabled") == 0) { enabledField = &field; }
            else if (std::strcmp(field.name, "components") == 0) { componentsField = &field; }

            if (nameField != nullptr &&
                enabledField != nullptr &&
                componentsField != nullptr) {
                break;
            }
        }

        // header
        if (enabledField) {
            void* data = (char*)selected + enabledField->offset;
            ImGui::Checkbox("##enabled", (bool*)data);
        }
        if (nameField) {
            void* data = (char*)selected + nameField->offset;
            ImGui::SameLine();
            ImGui::InputText("##name", (std::string*)data);
        }
        if (nameField || enabledField) {
            ImGui::Separator();
        }

        // fields
        for (auto& field : fields) {
            if (InspectorPanel::isSpecialFieldName(field.name)) { continue; }

            void* data = (char*)selected + field.offset;
            FieldInfo::DrawField(field, data);
        }

        // components
        if (componentsField) {
            void* data = (char*)selected + componentsField->offset;
            std::vector<Component*>* components = (std::vector<Component*>*)data;

            if (components) {
                for (Component*& component : *components) {
                    void* componentData = (char*)component;
                    FieldInfo componentField = {
                        component->name.c_str(),
                        component->GetTypeInfo()->name,
                        false,
                        0,
                        FieldFlags::None
                    };

                    bool componentOpened = ImGui::CollapsingHeader(FieldInfo::AppendId(component->name, component->id).c_str());

                    // right click context menu
                    if (ImGui::BeginPopupContextItem()) {
                        if (sceneObject != nullptr) {
                            if (ImGui::Selectable("Delete")) {
                                sceneObject->RemoveComponent(component);
                                delete component; // TODO safely handle delete
                                ImGui::EndPopup();
                                continue;
                            }
                        }
                        ImGui::EndPopup();
                    }

                    // drag & drop source
                    DragDropHandler::Source<Component>(component->GetTypeInfo()->name, component);

                    if (componentOpened) {
                        // custom draw handler (avoids a field name & other special fields)
                        InspectorPanel::DrawObjectAsField(componentField, componentData);
                    }
                }
            }
        }

        // add component button
        ImGui::Separator();
        if (sceneObject != nullptr) {
            AddComponentButton(sceneObject);
        }
    }

    ImGui::End();
}

void CondorEditor::InspectorPanel::DrawObjectAsField(FieldInfo& field, void* data) {
    Object* obj = (Object*)data;

    std::vector<FieldInfo> fields;
    obj->GetTypeInfo()->CollectFields(fields);

    for (auto& field : fields) {
        if (InspectorPanel::isSpecialFieldName(field.name)) { continue; }

        void* data = (char*)obj + field.offset;
        FieldInfo::DrawField(field, data);
    }
}

void CondorEditor::InspectorPanel::AddComponentButton(SceneObject* sceneObject) {
    static const char* addCompPopupName = "Add Component";

    if (sceneObject == nullptr) {
        return;
    }

    // add component popup
    if (ImGui::BeginPopup(addCompPopupName)) {
        std::vector<TypeInfo*> componentTypes =
            ReflectionRegistry::GetInheritedTypes(TypeResolver<Component>::Get()->name, false);
        for (TypeInfo* type : componentTypes) {
            if (type->CreateInstance == nullptr) {
                continue;
            }

            if (ImGui::Selectable(type->name)) {
                void* inst = type->CreateInstance();
                Component* component = static_cast<Component*>(inst);
                sceneObject->AddComponent(component);
            }
        }
        ImGui::EndPopup();
    }

    // add component button
    if (ImGui::Button(addCompPopupName)) {
        ImGui::OpenPopup(addCompPopupName);
    }
}
