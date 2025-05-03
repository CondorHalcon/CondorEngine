#include "suzane.h"

Suzane::Suzane(Material* material) {
    name = "CondorEngine::Suzane";
    mesh = AddComponent<Mesh>(new Mesh(
        ResourceManager::LoadMesh("meshes/suzane.obj"),
        material));
}
Suzane::Suzane() : Suzane(new Phong(ResourceManager::LoadTexture("textures/UVGrid.png"))) {}
