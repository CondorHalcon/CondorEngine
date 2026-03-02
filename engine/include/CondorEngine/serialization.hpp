#pragma once
#include "CondorEngine/pch.h"
#include "CondorEngine/math.hpp"
// std
#include <string>
#include <vector>
#include <type_traits>

namespace CondorEngine
{
    enum class DllExport FieldType
    {
        Int, Float, Bool,
        Vec2, Vec3, Vec4,
        String,
        Other
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

        template <typename T>
        static FieldType GetFieldType() {
            if (std::is_same_v<T, int> || std::is_same_v<T, unsigned int>) {
                return FieldType::Int;
            }
            if (std::is_same_v < T, float>) { return FieldType::Float; }
            if (std::is_same_v < T, bool>) { return FieldType::Bool; }
            if (std::is_same_v < T, Vector2>) { return FieldType::Vec2; }
            if (std::is_same_v < T, Vector3>) { return FieldType::Vec3; }
            if (std::is_same_v < T, Vector4>) { return FieldType::Vec4; }
            if (std::is_same_v<T, std::string>) { return FieldType::String; }

            return FieldType::Other;
        }
    };

    struct DllExport TypeInfo
    {
        std::string name;
        unsigned int typeId;
        TypeInfo* parent;
        std::vector<FieldInfo> fields;

        void CollectFields(std::vector<FieldInfo>& out) const {
            if (parent) {
                parent->CollectFields(out);
            }

            out.insert(out.end(), fields.begin(), fields.end());
        }
    };

    class DllExport ReflectionRegistry
    {
    public:
        static inline std::vector<TypeInfo*> registry = {};

        static void RegisterType(TypeInfo* type) {
            static unsigned int idIndex = 7; // start at the last value of FieldType then iterate forward

            if (type->typeId == 0) {
                idIndex++;
                type->typeId = idIndex;
            }
            registry.push_back(type);
        }

        template<typename Class, typename FieldType>
        static void RegisterField(TypeInfo& typeInfo, const char* name, FieldType Class::* member) {
            typeInfo.fields.push_back({
                name,
                FieldInfo::GetFieldType<FieldType>(),
                reinterpret_cast<size_t>(&(reinterpret_cast<Class*>(0)->*member))
                });
        }

        static TypeInfo* GetType(const unsigned int id) {
            for (TypeInfo* ti : registry) {
                if (ti->typeId == id) {
                    return ti;
                }
            }

            return nullptr;
        }
    };

#define REFLECT_ROOT_CLASS(Type)                             \
public:                                                      \
    using Self = Type;                                       \
    static TypeInfo* StaticTypeInfo()                        \
    {                                                        \
        return &s_TypeInfo;                                  \
    }                                                        \
    virtual TypeInfo* GetTypeInfo()                          \
    {                                                        \
        return &s_TypeInfo;                                  \
    }                                                        \
    virtual std::string GetType()                            \
    {                                                        \
        return s_TypeInfo.name;                              \
    }                                                        \
private:                                                     \
    static inline TypeInfo s_TypeInfo = {                    \
        #Type,                                               \
        0,                                                   \
        nullptr,                                             \
        {}                                                   \
    };

#define REFLECT_CLASS(Type, ParentType)                        \
public:                                                        \
    using Self = Type;                                         \
    static inline TypeInfo* StaticTypeInfo()                   \
    {                                                          \
        return &s_TypeInfo;                                    \
    }                                                          \
    virtual TypeInfo* GetTypeInfo() override                   \
    {                                                          \
        return Type::StaticTypeInfo();                         \
    }                                                          \
    virtual std::string GetType() override                     \
    {                                                          \
        return s_TypeInfo.name;                                \
    }                                                          \
private:                                                       \
    static inline TypeInfo s_TypeInfo = {                      \
        #Type,                                                 \
        0,                                                     \
        ParentType::StaticTypeInfo(),                          \
        {}                                                     \
    };

#define FIELD(type, name)                                       \
    type name;                                                  \
private:                                                        \
    struct AutoRegister_##name                                  \
    {                                                           \
        AutoRegister_##name()                                   \
        {                                                       \
            ReflectionRegistry::RegisterField<Self, type>(      \
                s_TypeInfo,                                     \
                #name,                                          \
                &Self::name);                                   \
        }                                                       \
    };                                                          \
    static inline AutoRegister_##name s_AutoRegister_##name;    \
public:
    
}