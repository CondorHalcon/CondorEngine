#pragma once
#include "CondorEngine/pch.h"
#include "CondorEngine/object.h"
#include "CondorEngine/rendering/renderer.h"
#include <string>
#include <vector>

namespace CondorEngine
{
    class ResourceManager;

    /// @brief Base resource class for filepath checking and collections.
    class DllExport ResourceBase : public Object
    {
        friend ResourceManager;
        REFLECT_CLASS(CondorEngine::ResourceBase, Object)
    private:
        /// @brief Default class constructor.
        ResourceBase();
    protected:
        /// @brief Class constructor.
        /// @param filepath Resource filepath.
        ResourceBase(std::string filepath);

        /// @brief Resource filepath.
        REFLECT_FIELD(std::string, filepath)

    public:
        /// @brief Resource filepath getter.
        /// @return Resource filepath.
        inline std::string getFilepath();
    };

    /// @brief Resource class for data storage.
    /// @tparam T Resource data type.
    template <typename T>
    class DllExport Resource : public ResourceBase
    {
        REFLECT_CLASS(CondorEngine::Resource<T>, ResourceBase)
        friend ResourceManager;
    public:
        /// @brief Class constructor.
        /// @param value 
        Resource(T value, std::string filepath) : ResourceBase(filepath), data(value) {}
    private:
        Resource() : ResourceBase("null"), data(T{}) {}

    private:
        /// @brief Resource data object.
        T data;

    public:
        /// @brief Resource data getter.
        /// @return Resource data object.
        inline T getData() { return data; }
    };

    template <typename T>
    struct TypeResolver<Resource<T>>
    {
        static TypeInfo* Get() {
            static TypeInfo typeInfo = {
                typeid(Resource<T>).name(), ResourceBase::StaticTypeInfo(), {}, {},
                nullptr,
                &TypeResolver<Resource<T>>::DrawField,
                &TypeResolver<Resource<T>>::DrawReference
            };
            return &typeInfo;
        }

        static void DrawField(FieldInfo& field, void* data) {
            TypeInfo* type = TypeResolver<Object>::Get();
            if (type) {
                type->DrawField(field, data);
            }
            else {
                FieldInfo::DrawField(field, data);
            }
        }
        static void DrawReference(FieldInfo& field, void* data) {
            TypeInfo* type = TypeResolver<Object>::Get();
            if (type) {
                type->DrawReference(field, data);
            }
            else {
                FieldInfo::DrawField(field, data);
            }
        }

    private:
        struct AutoRegister_Self
        {
            AutoRegister_Self() {
                ReflectionRegistry::RegisterType<Resource<T>>();
            }
        };
        static inline AutoRegister_Self _AutoRegisterSelf;
    };

    /// @brief Resource managing utility class.
    class DllExport ResourceManager
    {
    protected:
        /// @brief Collection of loaded resources.
        static std::vector<ResourceBase*> resources;

    public:
        /// @brief Initialize C++ resources.
        static void init();
        /// @brief Unload all resources.
        static void cleanup();

        /// @brief Load MeshData resource.
        /// @param filepath Resource filepath.
        /// @return MeshData object.
        static Resource<MeshData>* LoadMesh(const char* filepath);

        /// @brief Load MeshData resource.
        /// @param vertPath Vertex shader filepath.
        /// @param fragPath Fragment shader filepath.
        /// @return Shader object.
        static Resource<Shader>* LoadShader(const char* vertPath, const char* fragPath);

        /// @brief Load MeshData resource.
        /// @param filepath Resource filepath.
        /// @return Texture object.
        static Resource<Texture>* LoadTexture(const char* filepath);

    private:
        template <typename T>
        static Resource<T>* GetResource(const char* filepath) {
            for (auto r : resources) {
                if (r->filepath != std::string(filepath)) { continue; }
                if (static_cast<Resource<T>*>(r)) {
                    return static_cast<Resource<T>*>(r);
                }
            }
            return nullptr;
        }

        template <typename T>
        static Resource<T>* GetResource(const std::string& filepath) {
            return GetResource<T>(filepath.c_str());
        }
    };
}