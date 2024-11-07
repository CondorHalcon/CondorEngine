#include "defaultscene.h"
// internal
#include "../material.h"
#include "../sceneobjects/primitive.h"
#include "../sceneobjects/spectatorcam.h"

namespace CondorEngine
{
    DefaultScene::DefaultScene()
    {
        // directional light
        this->light = new DirectionalLight{ColorRGB{1, 1, 1}, Vector3{0, -.3, -.7}};

        // camera
        SpectatorCam *camera = this->Instantiate<SpectatorCam>(new SpectatorCam(), Vector3{0, 0, 5});
        camera->Rotate(Vector3{0, 180, 0});
        camera->camera->farClippingPlane = 100;

        // level
        SceneObject *floor = this->Instantiate<SceneObject>(new SceneObject(), Vector3{0, -5, 0});
        Mesh *floorMesh = floor->AddComponent<Mesh>(Primitive::MakeCube());
        floorMesh->material = new M_Lit(Texture::LoadTexture("textures/UVGrid.png"));
        Collider *floorCollider = floor->AddComponent<Collider>(new Collider(ColliderType::Plane));
        floor->Scale(Vector3{50, 1, 50});
    }

    DefaultScene::~DefaultScene()
    {
    }
}
