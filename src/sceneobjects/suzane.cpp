#include "CondorEngine/sceneobjects/suzane.h"

CondorEngine::Suzane::Suzane() {
    mesh = AddComponent<Mesh>(Mesh::LoadMeshFromFile("meshes/suzane.obj"));
}
