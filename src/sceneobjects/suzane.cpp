#include "CondorEngine/sceneobjects/suzane.h"
#include "CondorEngine/resourcemanager.h"
#include "CondorEngine/materials/phong.hpp"

CondorEngine::Suzane::Suzane(Material* material) {
    name = "CondorEngine::Suzane";
    mesh = AddComponent<Mesh>(new Mesh(
        ResourceManager::LoadMesh("CondorEngine/meshes/suzane.obj"),
        material));
}
CondorEngine::Suzane::Suzane() : Suzane(new Phong(ResourceManager::LoadTexture("CondorEngine/textures/UVGrid.png"))) {}
