#include "CondorEngine/object.h"
#include "CondorEngine/serialization.hpp"
#include "CondorEngine/debug.hpp"
#include "CondorEngine/resourcemanager.h"
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

    objectType->DrawField = [](FieldInfo& field, void* data, FieldDrawCallbacks* callbacks) {
        bool opened = ImGui::TreeNode(field.name);

        Object* obj = (Object*)data;

        // drag & drop source
        DragDropHandler::Source<Object>(field.type, obj);

        if (opened) {
            std::vector<FieldInfo> fields;
            obj->GetTypeInfo()->CollectFields(fields);

            for (auto& field : fields) {
                void* data = (char*)obj + field.offset;
                FieldInfo::DrawField(field, data, callbacks);
            }

            ImGui::TreePop();
        }
        };
    objectType->DrawReference = [](FieldInfo& field, void* data, FieldDrawCallbacks* callbacks) {
        Object* obj = *static_cast<Object* const*>(data);

        std::string displayName = obj != nullptr ? obj->name : "nullptr";
        char buffer[256];
        strncpy(buffer, displayName.c_str(), sizeof(buffer));

        ResourceBase* rsrc = dynamic_cast<ResourceBase*>(obj);
        ImGuiInputTextFlags flags = ImGuiInputTextFlags_ReadOnly;
        if (rsrc) {
            flags |= ImGuiInputTextFlags_ElideLeft;
        }
        ImGui::InputText(field.name, buffer, sizeof(buffer), flags);


        // editor double clicked
        if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)) {
            if (callbacks && callbacks->OnDoubleClick) {
                callbacks->OnDoubleClick(field, data);
            }
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
