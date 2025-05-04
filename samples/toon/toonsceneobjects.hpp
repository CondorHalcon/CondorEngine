#pragma once
#include <CondorEngine.hpp>
#include "toonmat.hpp"

class Ground : public SceneObject
{
public:
    Ground() {
        name = "Toon::Ground";
        mesh = AddComponent<Mesh>(new Mesh(ResourceManager::LoadMesh("meshes/ground.obj"), new ToonMat()));
    }

    Mesh* mesh;
};
