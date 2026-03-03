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

        virtual void OnGui() override {
            SceneObject* selected = Editor::Instance()->selectedSceneObject;
            ImGui::Begin(getTitle());

            if (selected) {
                std::vector<FieldInfo> fields;
                selected->GetTypeInfo()->CollectFields(fields);

                // header
                FieldInfo* nameField = nullptr;
                FieldInfo* enabledField = nullptr;
                for (auto& field : fields) {
                    if (std::strcmp(field.name, "name") == 0) { nameField = &field; }
                    else if (std::strcmp(field.name, "enabled") == 0) { enabledField = &field; }

                    if (nameField != nullptr && enabledField != nullptr) { break; }
                }
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
                    if (std::strcmp(field.name, "name") == 0 || std::strcmp(field.name, "enabled") == 0) { continue; }

                    void* data = (char*)selected + field.offset;
                    DrawField(field, data);
                }
            }

            ImGui::End();
        }
        void DrawField(FieldInfo& field, void* data) {
            TypeInfo* type = ReflectionRegistry::GetType(field.type);
            if (type != nullptr) {
                // fallback on parent draw if non is set
                TypeInfo* currentType = type;
                while (currentType->DrawField == nullptr && currentType->parent != nullptr) {
                    currentType = currentType->parent;
                }
                if (currentType->DrawField != nullptr) {
                    currentType->DrawField(field, data); // draw the field
                }
                else {
                    ImGui::Text(field.name); // no assigned draw field found
                }
            }
            else {
                ImGui::Text(field.name); // no registered type found
            }
        }
    };
}