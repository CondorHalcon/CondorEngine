#include "CondorEngine/scenes/defaultscene.h"
// internal
#include "CondorEngine/material.h"
#include "CondorEngine/materials/phong.hpp"
#include "CondorEngine/sceneobjects/primitive.h"
#include "CondorEngine/sceneobjects/spectatorcam.h"
#include "CondorEngine/resourcemanager.h"

namespace CondorEngine
{
    DefaultScene::DefaultScene()
    {
        // directional light
        light = DirectionalLight(ColorRGB{ .7, .7, .7 }, Vector3{ 0, -.3, -.7 });

        // camera
        SpectatorCam *camera = this->Instantiate<SpectatorCam>(new SpectatorCam(), Vector3{0, 0, 5});
        camera->Rotate(Vector3{ 0, 180, 0 });

        // level
        SceneObject *floor = this->Instantiate<SceneObject>(new SceneObject(), Vector3{0, -5, 0});
        Mesh* floorMesh = floor->AddComponent<Mesh>(new Mesh(Primitive::MakeCube()));
        floorMesh->material = new Phong(ResourceManager::LoadTexture("CondorEngine/textures/UVGrid.png"));
        Collider *floorCollider = floor->AddComponent<Collider>(new Collider(ColliderType::Plane));
        floor->Scale(Vector3{50, 1, 50});
    }

    DefaultScene::~DefaultScene()
    {
    }
}
