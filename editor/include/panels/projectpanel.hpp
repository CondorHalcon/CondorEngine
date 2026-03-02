#pragma once
#include "editorpanel.h"
#include "editor.h"
using namespace CondorEngine;

namespace CondorEditor
{
    class ProjectPanel : public EditorPanel
    {
    public:
        virtual const char* getTitle() { return "Project"; }

        virtual void OnGui() override {
            ImGui::Begin(getTitle());

            // TODO project directory

            ImGui::End();
        }
    };
}