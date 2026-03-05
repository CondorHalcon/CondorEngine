#include "panels/projectpanel.h"
#include <imgui.h>

void CondorEditor::ProjectPanel::OnGui() {
    ImGui::Begin(getTitle());

    // TODO project directory

    ImGui::End();
}