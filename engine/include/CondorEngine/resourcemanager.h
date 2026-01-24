#pragma once
#include "CondorEngine/pch.h"
#include "CondorEngine/rendering/renderer.h"
#include <string>
#include <vector>

namespace CondorEngine
{
    class ResourceManager;

    /// @brief Base resource class for filepath checking and collections.
    class DllExport ResourceBase
    {
        friend ResourceManager;
    protected:
        /// @brief Class constructor.
        /// @param filepath Resource filepath.
        ResourceBase(std::string filepath);

        /// @brief Resource filepath.
        std::string filepath;

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
        friend ResourceManager;
    public:
        /// @brief Class constructor.
        /// @param value 
        Resource(T value, std::string filepath) : ResourceBase(filepath), data(value) {}

    private:
        /// @brief Resource data object.
        T data;

    public:
        /// @brief Resource data getter.
        /// @return Resource data object.
        inline T getData() { return data; }
    };

    /// @brief Resource managing utility class.
    class DllExport ResourceManager
    {
    protected:
        /// @brief Collection of loaded resources.
        static std::vector<ResourceBase*> resources;

    public:
        /// @brief Unload all resources.
        static void cleanup();

        /// @brief Load MeshData resource.
        /// @param filepath Resource filepath.
        /// @return MeshData object.
        static MeshData LoadMesh(const char* filepath);

        /// @brief Load MeshData resource.
        /// @param vertPath Vertex shader filepath.
        /// @param fragPath Fragment shader filepath.
        /// @return Shader object.
        static Shader LoadShader(const char* vertPath, const char* fragPath);

        /// @brief Load MeshData resource.
        /// @param filepath Resource filepath.
        /// @return Texture object.
        static Texture LoadTexture(const char* filepath);

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