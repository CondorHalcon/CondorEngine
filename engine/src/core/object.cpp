#include "CondorEngine/object.h"
#include "CondorEngine/serialization.hpp"

CondorEngine::Object::Object(std::string name)
{
    this->name = name;
    this->enabled = true;
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

std::string CondorEngine::Object::GetType() {
    return "CondorEngine::Object";
}

void CondorEngine::Object::CollectFields(std::vector<CondorEngine::FieldInfo>& out) {
    out.push_back(FieldInfo{
            "name",
            FieldType::String,
            offsetof(Object, name),
            FieldFlags::Save
        });
    out.push_back(FieldInfo{
            "enabled",
            FieldType::Bool,
            offsetof(Object, enabled),
            FieldFlags::Save
        });
}
