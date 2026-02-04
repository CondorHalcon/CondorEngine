#pragma once
#include "CondorEngine/pch.h"
// std
#include <string>
#include <vector>

namespace CondorEngine
{
    enum class DllExport FieldType
    {
        Int, Float, Bool,
        Vec2, Vec3, Vec4,
        String,
        EntityRef
    };

    enum FieldFlags
    {
        None = 0,
        Editable = 1 << 0,
        Save = 1 << 1
    };

    struct DllExport FieldInfo
    {
        std::string name;
        FieldType type;
        size_t offset;
        FieldFlags flags;
    };
}