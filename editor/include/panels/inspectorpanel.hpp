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

                for (auto& field : fields) {
                    void* data = (char*)selected + field.offset;
                    DrawField(field, data);
                }
            }

            ImGui::End();
        }
        void DrawField(FieldInfo& field, void* data) {
            switch (field.type)
            {
            case FieldType::Int:
                ImGui::InputInt(field.name.c_str(), (int*)data);
                break;
            case FieldType::Float:
                ImGui::DragFloat(field.name.c_str(), (float*)data);
                break;
            case FieldType::Bool:
                ImGui::Checkbox(field.name.c_str(), (bool*)data);
                break;
            case FieldType::Vec2:
                ImGui::DragFloat2(field.name.c_str(), (float*)data);
                break;
            case FieldType::Vec3:
                ImGui::DragFloat3(field.name.c_str(), (float*)data);
                break;
            case FieldType::Vec4:
                ImGui::DragFloat4(field.name.c_str(), (float*)data);
                break;
            case FieldType::String:
                ImGui::InputText(field.name.c_str(), (std::string*)data);
                break;
            default:
                ImGui::Text(field.name.c_str());
                break;
            }
        }
    };
}