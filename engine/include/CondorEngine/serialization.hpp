#pragma once
#include "CondorEngine/pch.h"
// std
#include <string>
#include <vector>
#include <unordered_map>
// third party
#include <imgui.h>

namespace CondorEngine
{
#pragma region Type and Field Info
    enum FieldFlags
    {
        None = 0,
        Editable = 1 << 0,
        Save = 1 << 1
    };

    struct DllExport FieldInfo
    {
        const char* name;
        const char* type;
        bool pointer;
        size_t offset;
        FieldFlags flags;
    };

    struct DllExport TypeInfo
    {
        const char* name;
        TypeInfo* parent;
        std::vector<FieldInfo> fields;

        void (*Serialize)(void*);
        void (*Deserialize)(void*);
        void (*DrawField)(FieldInfo&, void*);
        void (*DrawInspector)(void*);

        void CollectFields(std::vector<FieldInfo>& out) const {
            if (parent) {
                parent->CollectFields(out);
            }

            out.insert(out.end(), fields.begin(), fields.end());
        }
    };
#pragma endregion

#pragma region Registry

    template <typename T>
    struct TypeResolver
    {
        static TypeInfo* Get() {
            return T::StaticTypeInfo();
        }
        static constexpr bool pointer = false;
    };
    // Pointer Resolver
    template <typename T>
    struct TypeResolver<T*>
    {
        static TypeInfo* Get() {
            return TypeResolver<T>::Get();
        }
        static constexpr bool pointer = true;
    };

    class DllExport ReflectionRegistry
    {
    private:
        static inline std::unordered_map<const char*, TypeInfo*> registry = {};
    public:
        template<typename T>
        static void RegisterType() {
            TypeInfo* type = TypeResolver<T>::Get();
            registry.insert({ type->name, type });
        }
        static TypeInfo* GetType(const char* type) {
            return registry[type];
        }

        template<typename Class, typename FieldType>
        static void RegisterField(TypeInfo& typeInfo, const char* name, FieldType Class::* member) {
            using CleanType = std::remove_cv_t<FieldType>; // extract base type from pointer and reference types
            constexpr bool isPointer = std::is_pointer_v<FieldType>;

            TypeInfo* fieldTypeInfo = TypeResolver<FieldType>::Get();

            typeInfo.fields.push_back({
                name,
                fieldTypeInfo->name,
                isPointer,
                reinterpret_cast<size_t>(&(reinterpret_cast<Class*>(0)->*member)),
                FieldFlags::None
                });
        }

        static void RegisterPrimitives() {
            RegisterType<int>();
            RegisterType<float>();
            RegisterType<bool>();
            RegisterType<std::string>();
            RegisterType<unsigned int>();
        }
    };

#pragma endregion

#pragma region Reflection MACROs

#define REFLECT_ROOT_CLASS(Type)                             \
public:                                                      \
    using Self = Type;                                       \
    static TypeInfo* StaticTypeInfo()                        \
    {                                                        \
        return &_TypeInfo;                                   \
    }                                                        \
    virtual TypeInfo* GetTypeInfo()                          \
    {                                                        \
        return &_TypeInfo;                                   \
    }                                                        \
    virtual std::string GetType()                            \
    {                                                        \
        return _TypeInfo.name;                               \
    }                                                        \
private:                                                     \
    static inline TypeInfo _TypeInfo = {                     \
        #Type,   /*name*/                                    \
        nullptr, /*parent*/                                  \
        {},      /*fields*/                                  \
        nullptr, /*Serialize*/                               \
        nullptr, /*Deserialize*/                             \
        nullptr, /*DrawProperty*/                            \
        nullptr, /*DrawInspector*/                           \
    };                                                       \
    struct AutoRegister_Self                                 \
    {                                                        \
        AutoRegister_Self() {                                \
            ReflectionRegistry::RegisterType<Type>();        \
        }                                                    \
    };                                                       \
    static inline AutoRegister_Self _AutoRegister_Self;

#define REFLECT_CLASS(Type, ParentType)                        \
public:                                                        \
    using Self = Type;                                         \
    static inline TypeInfo* StaticTypeInfo()                   \
    {                                                          \
        return &_TypeInfo;                                     \
    }                                                          \
    virtual TypeInfo* GetTypeInfo() override                   \
    {                                                          \
        return Type::StaticTypeInfo();                         \
    }                                                          \
    virtual std::string GetType() override                     \
    {                                                          \
        return _TypeInfo.name;                                 \
    }                                                          \
private:                                                       \
    static inline TypeInfo _TypeInfo = {                       \
        #Type,                          /*name*/               \
        ParentType::StaticTypeInfo(),   /*parent*/             \
        {},                             /*fields*/             \
        nullptr,                        /*Serialize*/          \
        nullptr,                        /*Deserialize*/        \
        nullptr,                        /*DrawProperty*/       \
        nullptr,                        /*DrawInspector*/      \
    };                                                         \
    struct AutoRegister_Self                                   \
    {                                                          \
        AutoRegister_Self() {                                  \
            ReflectionRegistry::RegisterType<Type>();          \
        }                                                      \
    };                                                         \
    static inline AutoRegister_Self _AutoRegister_Self;

#define FIELD(type, name)                                       \
    type name;                                                  \
private:                                                        \
    struct AutoRegister_##name                                  \
    {                                                           \
        AutoRegister_##name()                                   \
        {                                                       \
            ReflectionRegistry::RegisterField<Self, type>(      \
                _TypeInfo,                                      \
                #name,                                          \
                &Self::name);                                   \
        }                                                       \
    };                                                          \
    static inline AutoRegister_##name s_AutoRegister_##name;    \
public:

#pragma endregion

#pragma region Primitives
    
    template <>
    struct TypeResolver<int>
    {
        static TypeInfo* Get() {
            static TypeInfo typeInfo = {
                "int", nullptr, {},
                nullptr,
                nullptr,
                [](FieldInfo& field, void* data) { ImGui::InputInt(field.name, (int*)data); },
                nullptr
            };
            return &typeInfo;
        }
    };
    template <>
    struct TypeResolver<float>
    {
        static TypeInfo* Get() {
            static TypeInfo typeInfo = {
                "float", nullptr, {},
                nullptr,
                nullptr,
                [](FieldInfo& field, void* data) { ImGui::DragFloat(field.name, (float*)data); },
                nullptr
            };
            return &typeInfo;
        }
    };
    template <>
    struct TypeResolver<bool>
    {
        static TypeInfo* Get() {
            static TypeInfo typeInfo = {
                "bool", nullptr, {},
                nullptr,
                nullptr,
                [](FieldInfo& field, void* data) { ImGui::Checkbox(field.name, (bool*)data); },
                nullptr
            };
            return &typeInfo;
        }
    };
    template <>
    struct TypeResolver<std::string>
    {
        static TypeInfo* Get() {
            static TypeInfo typeInfo = {
                "std::string", nullptr, {},
                nullptr,
                nullptr,
                nullptr,
                nullptr
            };
            return &typeInfo;
        }
    };

    template <>
    struct TypeResolver<unsigned int>
    {
        static TypeInfo* Get() {
            static TypeInfo typeInfo = {
                "unsigned int", nullptr, {},
                nullptr,
                nullptr,
                [](FieldInfo& field, void* data) { ImGui::InputInt(field.name, (int*)data); },
                nullptr
            };
            return &typeInfo;
        }
    };

#pragma endregion
}