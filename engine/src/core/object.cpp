#include "CondorEngine/object.h"
#include "CondorEngine/serialization.hpp"
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
        if (ImGui::TreeNode(field.name)) {
            Object* obj = (Object*)data;

            std::vector<FieldInfo> fields;
            obj->GetTypeInfo()->CollectFields(fields);

            for (auto& field : fields) {
                void* data = (char*)obj + field.offset;
                FieldInfo::DrawField(field, data);
            }
            
            ImGui::TreePop();
        }
        };
}
