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

        static void DrawField(FieldInfo& field, void* data);
    };

    struct DllExport TypeInfo
    {
        const char* name;
        TypeInfo* parent;
        std::vector<FieldInfo> fields;

        void* (*CreateInstance)();
        void (*DrawField)(FieldInfo&, void*);
        void (*DrawReference)(FieldInfo&, void*);

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
    public:
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
    static Type* CreateInstance() { return new Type(); }     \
private:                                                     \
    static inline TypeInfo _TypeInfo = {                     \
        #Type,          /*name*/                             \
        nullptr,        /*parent*/                           \
        {},             /*fields*/                           \
        []()->void* {       /*CreateInstance*/               \
            return (char*)CreateInstance();                  \
        },                                                   \
        nullptr,        /*DrawProperty*/                     \
        nullptr,        /*DrawInspector*/                    \
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
    static inline Type* CreateInstance() { return new Type(); }\
private:                                                       \
    static inline TypeInfo _TypeInfo = {                       \
        #Type,                          /*name*/               \
        ParentType::StaticTypeInfo(),   /*parent*/             \
        {},                             /*fields*/             \
        []()->void* {                   /*CreateInstance*/     \
            return (char*)CreateInstance();                    \
        },                                                     \
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

#pragma region Primitive Resolvers
    
    template <>
    struct TypeResolver<int> { static TypeInfo* Get(); };

    template <>
    struct TypeResolver<float> { static TypeInfo* Get(); };

    template <>
    struct TypeResolver<bool> { static TypeInfo* Get(); };

    template <>
    struct TypeResolver<unsigned int> { static TypeInfo* Get(); };

#pragma endregion

#pragma region std Resolvers

    template <>
    struct TypeResolver<std::string> { static TypeInfo* Get(); };
    
    template <typename T>
    struct TypeResolver<std::vector<T>>
    {
        static TypeInfo* Get() {
            static TypeInfo typeInfo = {
                typeid(std::vector<T>).name(), nullptr, {},
                nullptr,
                &TypeResolver<std::vector<T>>::DrawField,
                nullptr
            };
            return &typeInfo;
        }
        static void DrawField(FieldInfo& field, void* data) {
            TypeInfo* itemType = TypeResolver<T>::Get();

            if (itemType == nullptr) {
                if (ImGui::TreeNode(field.name)) { ImGui::TreePop(); }
                return;
            }

            if (ImGui::TreeNode(field.name)) {
                std::vector<T>* list = (std::vector<T>*)data;
                
                constexpr bool itemIsPointer = std::is_pointer_v<T>;

                for (std::size_t i = 0; i < list->size(); ++i) {
                    void* itemData = (char*)&(*list)[i];
                    std::string itemName = std::to_string(i);
                    FieldInfo itemInfo = {
                        itemName.c_str(),
                        itemType->name,
                        itemIsPointer,
                        0,
                        FieldFlags::None
                    };
                    FieldInfo::DrawField(itemInfo, (void*)itemData);
                }

                ImGui::TreePop();
            }
        }
    private:
        struct AutoRegister_Self
        {
            AutoRegister_Self() {
                ReflectionRegistry::RegisterType<std::vector<T>>();
            }
        };
        static inline AutoRegister_Self _autoRegister_Self;
    };

#pragma endregion
}