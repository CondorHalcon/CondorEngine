#include "CondorEngine/resourcemanager.h"
#include "CondorEngine/debug.hpp"
#include "CondorEngine/sceneobjects/primitive.h"

std::vector<CondorEngine::ResourceBase*> CondorEngine::ResourceManager::resources = std::vector<CondorEngine::ResourceBase*>();

CondorEngine::ResourceBase::ResourceBase(std::string filepath) : Object("Resource") {
    this->filepath = filepath;
}

CondorEngine::ResourceBase::ResourceBase() : Object("Resource") {
}

inline std::string CondorEngine::ResourceBase::getFilepath() { return filepath; }

void CondorEngine::ResourceManager::init() {
    Primitive::simpleCubeMesh = new Resource<MeshData>(Primitive::MakeSimpleCube(), "Primitive::simpleCubeMesh");
    Primitive::cubeMesh = new Resource<MeshData>(Primitive::MakeSimpleCube(), "Primitive::cubeMesh");
    Primitive::planeMesh = new Resource<MeshData>(Primitive::MakeSimpleCube(), "Primitive::planeMesh");
    Primitive::sphereMesh = new Resource<MeshData>(Primitive::MakeSimpleCube(), "Primitive::sphereMesh");
    Primitive::cylinderMesh = new Resource<MeshData>(Primitive::MakeSimpleCube(), "Primitive::cylinderMesh");
}

void CondorEngine::ResourceManager::cleanup() {
    for (auto resource : resources) {
        Debug::Log("CondorEngine::ResourceManager :: Unloading resource [" + resource->filepath + "]");
        if (static_cast<Resource<MeshData>*>(resource)) {
            MeshData::FreeMesh(static_cast<Resource<MeshData>*>(resource)->getData());
            continue;
        }
        if (static_cast<Resource<Shader>*>(resource)) {
            Shader::FreeShader(static_cast<Resource<Shader>*>(resource)->getData());
            continue;
        }
        if (static_cast<Resource<Texture>*>(resource)) {
            Texture::FreeTexture(static_cast<Resource<Texture>*>(resource)->getData());
            continue;
        }
    }
}

CondorEngine::Resource<CondorEngine::MeshData>* CondorEngine::ResourceManager::LoadMesh(const char* filepath) {
    // check if the resource has already been loaded
    Resource<MeshData>* resource = GetResource<MeshData>(filepath);
    if (resource != nullptr) { return resource; }

    // load from file
    Debug::Log("CondorEngine::ResourceManager :: Loading resource [" + std::string(filepath) + "] as CondorEngine::MeshData");
    resource = new Resource<MeshData>(MeshData::LoadMesh(filepath), filepath);
    resources.push_back(resource);

    return resource;
}

CondorEngine::Resource<CondorEngine::Shader>* CondorEngine::ResourceManager::LoadShader(const char* vertPath, const char* fragPath) {
    std::string filepath = std::string(vertPath) + ";" + std::string(fragPath);

    // check if the resource has already been loaded
    Resource<Shader>* resource = GetResource<Shader>(filepath);
    if (resource != nullptr) { return resource; }

    // load from file
    Debug::Log("CondorEngine::ResourceManager :: Loading resources [" + std::string(vertPath) + "] and [" + std::string(fragPath) + "] as CondorEngine::Shader");
    resource = new Resource<Shader>(Shader::LoadShader(vertPath, fragPath), filepath);
    resources.push_back(resource);

    return resource;
}

CondorEngine::Resource<CondorEngine::Texture>* CondorEngine::ResourceManager::LoadTexture(const char* filepath) {
    // check if the resource has already been loaded
    Resource<Texture>* resource = GetResource<Texture>(filepath);
    if (resource != nullptr) { return resource; }

    // load from file
    Debug::Log("CondorEngine::ResourceManager :: Loading resource [" + std::string(filepath) + "] as CondorEngine::MeshData");
    resource = new Resource<Texture>(Texture::LoadTexture(filepath), filepath);
    resources.push_back(resource);

    return resource;
}
