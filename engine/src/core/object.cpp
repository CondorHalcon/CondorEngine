#include "CondorEngine/object.h"
#include "CondorEngine/serialization.hpp"
#include "CondorEngine/debug.hpp"
#include <imgui.h>

CondorEngine::Object::Object(std::string name)
{
    this->name = name;
    this->enabled = true;

    static unsigned int idIndex = 0;
    this->id = idIndex++;
}

CondorEngine::Object::Object() : Object("Object") {}

std::string CondorEngine::Object::to_string()
{
    std::string str = name;
    str.append("(");
    str.append(GetType());
    str.append(")");
    return str;
}

CondorEngine::Object::AutoRegister_Draw::AutoRegister_Draw() {
    TypeInfo* objectType = TypeResolver<Object>::Get();

    objectType->DrawField = [](FieldInfo& field, void* data) {
        bool opened = ImGui::TreeNode(field.name);

        Object* obj = (Object*)data;

        // drag & drop source
        DragDropHandler::Source<Object>(field.type, obj);

        if (opened) {
            std::vector<FieldInfo> fields;
            obj->GetTypeInfo()->CollectFields(fields);

            for (auto& field : fields) {
                void* data = (char*)obj + field.offset;
                FieldInfo::DrawField(field, data);
            }

            ImGui::TreePop();
        }
        };
    objectType->DrawReference = [](FieldInfo& field, void* data) {
        Object* obj = *static_cast<Object* const*>(data);

        std::string objName = obj != nullptr ? obj->name : "nullptr";
        char buffer[256];
        strncpy(buffer, objName.c_str(), sizeof(buffer));
        ImGui::InputText(field.name, buffer, sizeof(buffer), ImGuiInputTextFlags_ReadOnly);

        // editor double clicked
        if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)) {
            Debug::Log("Object :: Double-clicked Object ref"); // TODO handle double clicked
        }

        // right click context menu
        if (ImGui::BeginPopupContextItem()) {
            ImGui::EndPopup();
        }

        // drag & drop target
        Object* payloadObject = DragDropHandler::Target<Object>(field.type);
        if (payloadObject != nullptr) {
            *obj = *payloadObject;
        }
        };
}
