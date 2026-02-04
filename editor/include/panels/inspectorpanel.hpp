#pragma once
#include "editorpanel.h"
#include "serialization.hpp"
#include <string>
using namespace CondorEngine;

namespace CondorEditor
{
    class InspectorPanel : public EditorPanel
    {
    public:
        virtual void OnGui() override {
            SceneObject* selected = Editor::Instance()->selectedSceneObject;
            ImGui::Begin("Inspector");

            if (selected) {
                std::vector<FieldInfo> fields;
                selected->CollectFields(fields);

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
            case FieldType::Float:
                ImGui::DragFloat(field.name.c_str(), (float*)data);
                break;
            default:
                ImGui::Text(field.name.c_str());
                break;
            }
        }
    };
}