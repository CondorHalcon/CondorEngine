#pragma once
#define CondorEngine_Serialization
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
    enum class FieldFlags
    {
        None = 0,
        Editable = 1 << 0,
        Save = 1 << 1
    };

    struct EnumValueInfo
    {
        const char* name;
        int64_t value;
    };

    struct FieldDrawCallbacks;

    struct DllExport FieldInfo
    {
        const char* name;
        const char* type;
        bool pointer;
        size_t offset;
        FieldFlags flags;

        static void DrawField(FieldInfo& field, void* data, FieldDrawCallbacks* callbacks);
        static std::string AppendId(std::string name, unsigned int id);
        static const char* AppendId(const char* name, unsigned int id);
    };

    struct FieldDrawCallbacks
    {
        void (*OnDoubleClick)(FieldInfo&, void*);
    };

    struct DllExport TypeInfo
    {
        const char* name;
        TypeInfo* parent;
        std::vector<FieldInfo> fields;
        std::vector<EnumValueInfo> enumValues;

        void* (*CreateInstance)();
        void (*DrawField)(FieldInfo&, void*, FieldDrawCallbacks*);
        void (*DrawReference)(FieldInfo&, void*, FieldDrawCallbacks*);

        void CollectFields(std::vector<FieldInfo>& out) const {
            if (parent) {
                parent->CollectFields(out);
            }

            out.insert(out.end(), fields.begin(), fields.end());
        }

        bool isEnum() {
            return fields.size() == 0 && enumValues.size() > 0;
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

            typeInfo.fields.push_back(FieldInfo{
                name,
                fieldTypeInfo->name,
                isPointer,
                reinterpret_cast<size_t>(&(reinterpret_cast<Class*>(0)->*member)),
                FieldFlags::None
                });
        }

        template<typename T>
        static void RegisterEnum() {
            RegisterType<T>();
        }

        template<typename EnumType>
        static void RegisterEnumValue(const char* name, int64_t value) {
            TypeInfo* type = TypeResolver<EnumType>::Get();
            type->enumValues.push_back(EnumValueInfo{ name, value });
        }

        static void RegisterPrimitives() {
            RegisterType<int>();
            RegisterType<float>();
            RegisterType<bool>();
            RegisterType<std::string>();
            RegisterType<unsigned int>();
        }

        static std::vector<TypeInfo*> GetInheritedTypes(const char* base, bool includeSelf = true) {
            if (base == nullptr) {
                return {};
            }

            std::vector<TypeInfo*> subTypes = {};
            for (auto entry : registry) {
                TypeInfo* currentType = entry.second;

                // this is the base type
                if (strcmp(currentType->name, base) == 0 && includeSelf) {
                    subTypes.push_back(currentType);
                    continue;
                }

                while (currentType->parent != nullptr) {
                    if (strcmp(currentType->parent->name, base) == 0) {
                        subTypes.push_back(entry.second);
                        break;
                    }
                    currentType = currentType->parent;
                }
            }
            return subTypes;
        }

        static std::vector<TypeInfo*> GetInheritedTypes(TypeInfo* base, bool includeSelf = true) {
            if (base == nullptr) {
                return {};
            }
            return GetInheritedTypes(base->name, includeSelf);
        }

        static bool IsInheritedType(const char* current, const char* parent) {
            if (current == nullptr || parent == nullptr) {
                return false;
            }
            if (strcmp(current, parent) == 0) {
                return true;
            }

            std::vector<TypeInfo*> list = GetInheritedTypes(parent);
            for (TypeInfo*& item : list) {
                if (strcmp(current, item->name) == 0) {
                    return true;
                }
            }
            return false;
        }

        static bool IsInheritedType(TypeInfo* current, TypeInfo* parent) {
            if (current == nullptr || parent == nullptr) {
                return false;
            }
            return IsInheritedType(current->name, parent->name);
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
        {},             /*enumValues*/                       \
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
        {},                             /*enumValues*/         \
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

#define REFLECT_STRUCT(Type)   \
    REFLECT_ROOT_CLASS(Type)   \
public:

#define REFLECT_FIELD(type, name)                               \
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
public:                                                         \
    type name;

#define REFLECT_ENUM_BEGIN(EnumType)                                        \
template<>                                                                  \
struct TypeResolver<EnumType>                                               \
{                                                                           \
    static TypeInfo* Get()                                                  \
    {                                                                       \
        static TypeInfo _TypeInfo = {                                       \
            typeid(EnumType).name(), nullptr, {}, {},                       \
            nullptr,                                                        \
            &TypeResolver<EnumType>::DrawField,                             \
            &TypeResolver<EnumType>::DrawField                              \
        };                                                                  \
        return &_TypeInfo;                                                  \
    }                                                                       \
    static void DrawField(FieldInfo& field, void* data, FieldDrawCallbacks* callbacks) {\
        TypeInfo* type = TypeResolver<EnumType>::Get();                     \
        EnumType* value = (EnumType*)data;                                  \
        if (type) {                                                         \
            std::vector<const char*> names = std::vector<const char*>{};    \
            for (auto& item : type->enumValues) {                           \
                names.push_back(item.name);                                 \
            }                                                               \
            ImGui::Combo(field.name, (int*)value, names.data(), static_cast<int>(names.size()));\
        }                                                                   \
    }                                                                       \
    struct EnumReflection_##EnumType                                        \
    {                                                                       \
        EnumReflection_##EnumType() {                                       \
            TypeInfo* type = TypeResolver<EnumType>::Get();                 \
            ReflectionRegistry::RegisterEnum<EnumType>();

#define REFLECT_ENUM_VALUE(EnumType, value)   \
            ReflectionRegistry::RegisterEnumValue<EnumType>(#value, (int64_t)value);

#define REFLECT_ENUM_END(EnumType)                                      \
        }                                                               \
    };                                                                  \
    static inline EnumReflection_##EnumType _EnumReflection_##EnumType; \
};

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
                typeid(std::vector<T>).name(), nullptr, {}, {},
                nullptr,
                &TypeResolver<std::vector<T>>::DrawField,
                nullptr
            };
            return &typeInfo;
        }
        static void DrawField(FieldInfo& field, void* data, FieldDrawCallbacks* callbacks) {
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
                    FieldInfo::DrawField(itemInfo, (void*)itemData, callbacks);
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

#pragma region Drag & Drop

    class DllExport DragDropHandler
    {
    public:
        template <typename T>
        static void Source(const char* type, T*& data) {
            if (data == nullptr) {
                return;
            }

            if (ImGui::BeginDragDropSource()) {
                bool sent = ImGui::SetDragDropPayload(type, &data, sizeof(T*));
                ImGui::Text("Dragging item(%s)", type); // TODO solve for item name
                ImGui::EndDragDropSource();
            }
        }

        template <typename T>
        static void Source(TypeInfo* type, T*& data) {
            if (type == nullptr) {
                return;
            }
            Source<T>(type->name, data);
        }

        template <typename T>
        static T* Target(const char* type) {
            if (!ImGui::BeginDragDropTarget()) {
                return nullptr;
            }

            std::vector<TypeInfo*> inheritedTypes = ReflectionRegistry::GetInheritedTypes(type, true);
            for (TypeInfo* subType : inheritedTypes) {
                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(subType->name)) {
                    T* data = nullptr;

                    if (payload->Data != nullptr) {
                        data = *static_cast<T* const*>(payload->Data);
                    }

                    ImGui::EndDragDropTarget();
                    return data;
                }
            }
            
            ImGui::EndDragDropTarget();
            return nullptr;
        }
        template <typename T>
        static T* Target(TypeInfo* type) {
            if (type == nullptr) {
                return nullptr;
            }

            return Target<T>(type->name);
        }
    };

#pragma endregion
}