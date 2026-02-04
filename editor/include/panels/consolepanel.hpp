#pragma once
#include "editorpanel.h"
#include "editor.h"
using namespace CondorEngine;

namespace CondorEditor
{
    class ConsolePanel : public EditorPanel
    {
    public:
        virtual void OnGui() override {
            ImGui::Begin("Console");

            // TODO list console logs

            ImGui::End();
        }
    };
}