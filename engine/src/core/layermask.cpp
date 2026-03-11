#include "CondorEngine/layermask.h"
#include "CondorEngine/application.h"

CondorEngine::LayerMask::LayerMask(unsigned int value) {
    this->value = value;
}

std::vector<std::string> CondorEngine::LayerMask::getLayers() {
    return Application::GetLayers(value);
}

std::string CondorEngine::LayerMask::getLabel() {
    return std::string("LayerMask");
}

CondorEngine::LayerMask::AutoRegister_LayerMask_Draw::AutoRegister_LayerMask_Draw() {
    _TypeInfo.DrawField = [](FieldInfo& field, void* data, FieldDrawCallbacks* callbacks) {
        LayerMask* layerMask = (LayerMask*)data;
        std::string preview;

        // preview
        for (int i = 0; i < Application::layerNames.size(); i++) {
            unsigned int layer = (unsigned int)glm::pow(2, i);
            if (layer & layerMask->value) {
                if (!preview.empty()) { preview += ", "; }
                preview += Application::layerNames[i];
            }
        }
        if (preview.empty()) { preview = "None"; }

        // widget
        if (ImGui::BeginCombo(field.name, preview.c_str())) {
            for (int i = 0; i < Application::layerNames.size(); i++) {
                unsigned int layer = (unsigned int)glm::pow(2, i);
                bool enabled = layer & layerMask->value;
                if (ImGui::Selectable(Application::layerNames[i].c_str(), enabled, ImGuiSelectableFlags_DontClosePopups)) {
                    if (enabled) { layerMask->value &= ~layer; }
                    else { layerMask->value |= layer; }
                }
            }
            ImGui::EndCombo();
        }
        };
}