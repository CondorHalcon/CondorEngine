#pragma once
#include "editorpanel.h"
#include "editor.h"
using namespace CondorEngine;

namespace CondorEditor
{
    class HierarchyPanel : public EditorPanel
    {
    public:
        virtual const char* getTitle() { return "Hierarchy"; }

        virtual void OnGui() override {
            ImGui::Begin(getTitle());

            if (Application::Instance()->activeScene != nullptr) {

                for (auto& obj : Application::Instance()->activeScene->hierarchy) {
                    if (ImGui::Selectable(obj->name.c_str(), obj == Editor::Instance()->selectedSceneObject))
                        Editor::Instance()->selectedSceneObject = obj;
                }
            }

            ImGui::End();
        }
    };
}