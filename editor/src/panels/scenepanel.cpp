#include "panels/scenepanel.h"
#include <imgui.h>

void CondorEditor::ScenePanel::OnGui() {
    ImGui::Begin(getTitle());

    /*SceneViewRenderFeature* svrf = SceneViewRenderFeature::Instance();

    ImVec2 avail = ImGui::GetContentRegionAvail();
    int newWidth = (int)avail.x;
    int newHeight = (int)avail.y;

    if (newWidth > 0 && newHeight > 0 &&
        (newWidth != svrf->sceneSize.x || newHeight != svrf->sceneSize.y)) {
        svrf->CreateSceneFramebuffer(newWidth, newHeight);
    }

    ImGui::Image(
        (ImTextureID)(intptr_t)svrf->sceneColorTex,
        ImVec2((float)svrf->sceneSize.x, (float)svrf->sceneSize.y),
        ImVec2(0, 1), ImVec2(1, 0) // Flip Y
    );*/

    ImGui::End();
}