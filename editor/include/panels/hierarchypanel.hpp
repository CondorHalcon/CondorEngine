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
                    DrawObjectHierarchy(obj);
                }
            }

            ImGui::End();
        }
    private:
        static bool DrawObjectHierarchy(SceneObject* object) {
            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_DefaultOpen;

            if (object == Editor::Instance()->selectedSceneObject) {
                flags |= ImGuiTreeNodeFlags_Selected;
            }

            if (object->children.size() <= 0) {
                flags |= ImGuiTreeNodeFlags_Leaf;
            }

            bool opened = ImGui::TreeNodeEx((void*)&object->id, flags, "%s", object->name.c_str());

            if (ImGui::IsItemClicked()) {
                Editor::Instance()->selectedSceneObject = object;
            }

            if (opened && object->children.size() > 0) {
                for (auto& child : object->children) {
                    DrawObjectHierarchy(child);
                }
            }

            if (opened) {
                ImGui::TreePop();
            }

            return opened;
        }
    };
}