#pragma once
#include "editorpanel.h"
#include "serialization.hpp"
#include <misc/cpp/imgui_stdlib.h>
#include <misc/cpp/imgui_stdlib.cpp>
#include <string>
using namespace CondorEngine;

namespace CondorEditor
{
    class InspectorPanel : public EditorPanel
    {
    public:
        virtual const char* getTitle() { return "Inspector"; }

        static inline std::vector<std::string> specialFieldNames = { "name", "enabled", "components", "children" };

        static inline bool isSpecialFieldName(const char* fieldName) {
            for (std::string name : specialFieldNames) {
                if (name == fieldName) { return true; }
            }

            return false;
        }

        virtual void OnGui() override {
            Object* selected = Editor::Instance()->selectedSceneObject;
            ImGui::Begin(getTitle());

            if (selected) {
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
                        for (Component* component : *components) {
                            void* componentData = (char*)component;
                            FieldInfo componentInfo = {
                                component->name.c_str(),
                                component->GetTypeInfo()->name,
                                false,
                                0,
                                FieldFlags::None
                            };
                            if (ImGui::CollapsingHeader(component->name.c_str())) {
                                // custom draw handler (avoids a field name entry & special fields)
                                InspectorPanel::DrawObjectAsField(componentInfo, componentData);
                            }
                        }
                    }
                }
            }

            ImGui::End();
        }
    private:
        static void DrawObjectAsField(FieldInfo& field, void* data) {
            Object* obj = (Object*)data;

            std::vector<FieldInfo> fields;
            obj->GetTypeInfo()->CollectFields(fields);

            for (auto& field : fields) {
                if (InspectorPanel::isSpecialFieldName(field.name)) { continue; }

                void* data = (char*)obj + field.offset;
                FieldInfo::DrawField(field, data);
            }
        }
    };
}