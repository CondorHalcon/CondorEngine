#include "CondorEngine/serialization.hpp"
#include <misc/cpp/imgui_stdlib.h>
#include <misc/cpp/imgui_stdlib.cpp>

void CondorEngine::FieldInfo::DrawField(FieldInfo& field, void* data) {
    TypeInfo* type = ReflectionRegistry::GetType(field.type);
    if (type != nullptr) {
        TypeInfo* fallbackType = type;
        if (!field.pointer) {
            // fallback on parent draw if non is set
            while (fallbackType->DrawField == nullptr && fallbackType->parent != nullptr) {
                fallbackType = fallbackType->parent;
            }
            if (fallbackType->DrawField != nullptr) {
                fallbackType->DrawField(field, data); // draw the field
            }
            else {
                ImGui::Text(field.name); // no assigned draw field found
            }
        }
        else {
            // fallback on parent draw if non is set
            while (fallbackType->DrawReference == nullptr && fallbackType->parent != nullptr) {
                fallbackType = fallbackType->parent;
            }
            if (fallbackType->DrawReference != nullptr) {
                fallbackType->DrawReference(field, data); // draw the reference
            }
            else {
                ImGui::Text(field.name); // no assigned draw field found
            }
        }
    }
    else {
        ImGui::Text(field.name); // no registered type found
    }
}

std::string CondorEngine::FieldInfo::AppendId(std::string name, unsigned int id) {
    return std::string(name).append("##").append(std::to_string(id));
}

const char* CondorEngine::FieldInfo::AppendId(const char* name, unsigned int id) {
    return AppendId(std::string{ name }, id).c_str();
}

CondorEngine::TypeInfo* CondorEngine::TypeResolver<int>::Get() {
    static TypeInfo typeInfo = {
        "int", nullptr, {}, {},
        nullptr,
        [](FieldInfo& field, void* data) { ImGui::InputInt(field.name, (int*)data); },
        nullptr
    };
    return &typeInfo;
}

CondorEngine::TypeInfo* CondorEngine::TypeResolver<float>::Get() {
    static TypeInfo typeInfo = {
        "float", nullptr, {}, {},
        nullptr,
        [](FieldInfo& field, void* data) { ImGui::DragFloat(field.name, (float*)data); },
        nullptr
    };
    return &typeInfo;
}

CondorEngine::TypeInfo* CondorEngine::TypeResolver<bool>::Get() {
    static TypeInfo typeInfo = {
        "bool", nullptr, {}, {},
        nullptr,
        [](FieldInfo& field, void* data) { ImGui::Checkbox(field.name, (bool*)data); },
        nullptr
    };
    return &typeInfo;
}

CondorEngine::TypeInfo* CondorEngine::TypeResolver<unsigned int>::Get()
{
    static TypeInfo typeInfo = {
        "unsigned int", nullptr, {}, {},
        nullptr,
        [](FieldInfo& field, void* data) { ImGui::InputInt(field.name, (int*)data); },
        nullptr
    };
    return &typeInfo;
}

CondorEngine::TypeInfo* CondorEngine::TypeResolver<std::string>::Get() {
    static TypeInfo typeInfo = {
        "std::string", nullptr, {}, {},
        nullptr,
        [](FieldInfo& field, void* data) { ImGui::InputText(field.name, (std::string*)data); },
        nullptr
    };
    return &typeInfo;
}
 