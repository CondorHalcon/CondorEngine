#include "CondorEngine/sceneobjects/suzane.h"
#include "CondorEngine/resourcemanager.h"

CondorEngine::Suzane::Suzane() {
    mesh = AddComponent<Mesh>(new Mesh(ResourceManager::LoadMesh("meshes/suzane.obj")));
}
