#include "panels/consolepanel.h"
#include <imgui.h>

void CondorEditor::ConsolePanel::OnGui() {
    ImGui::Begin(getTitle());

    // TODO list console logs

    ImGui::End();
}