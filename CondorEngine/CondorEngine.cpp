// third party
#include "glew/glew.h"
#include "glm/ext.hpp"
#include "glfw/glfw3.h"
// internal
#include "diagnostics.h"
#include "debug.hpp"
#include "time.h"
#include "math.h"
#include "application.h"
#include "renderer.h"
#include "physics.h"
#include "scene.h"
#include "sceneobject.h"
#include "material.h"
#include "scenes/defaultscene.h"
#include "sceneobjects/spectatorcam.h"
#include "sceneobjects/primitive.h"
#include "components/collider.h"
#include "components/mesh.h"
#include "components/rigidbody.h"
// std
#include <iostream>
#include <string>

using namespace CondorEngine;

#pragma region Implementation Classes

/// @brief Demo wall class.
class Wall : public SceneObject
{
public:
    /// @brief Class constructor.
    Wall() : SceneObject()
    {
        this->name = "Wall";
        this->collider = this->AddComponent<Collider>(new Collider(ColliderType::Plane));
        this->collider->plane = PlaneSize{Axis::Up, Vector2{1, 1}};
        this->mesh = this->AddComponent<Mesh>(Primitive::MakePlane());
        this->mesh->material = new M_Lit(Texture::LoadTexture("textures/UVGrid.png"));
    }
    /// @brief Wall collider component.
    Collider *collider;
    /// @brief Wall mesh component.
    Mesh *mesh;
};

#pragma endregion

#pragma region Main

int main()
{
    Application* app = Application::Instance();
    if (!app->init(640, 480, "CondorEngine")) {
        Debug::LogError("Failed to initialise application.");
        return -1;
    }
    Time::fixedTimeStep = .02f;

    diagnostics::Environment();

    // Scene
    Scene *scene = Application::activeScene = new DefaultScene();

    // material
    M_Lit *pMat = new M_Lit(Texture::LoadTexture("textures/ColorGrid.png"));

    // primitive mesh
    Primitive *prim = scene->Instantiate(
        new Primitive(PrimitiveType::CubeMesh, pMat),
        Vector3{0, .5f, 0});

    // primitive mesh 2
    Primitive *prim2 = scene->Instantiate(
        new Primitive(PrimitiveType::SphereMesh, pMat),
        Vector3{0, 0, 0});

    // primitive mesh 3
    Primitive *prim3 = scene->Instantiate(
        new Primitive(PrimitiveType::CubeMesh, pMat),
        Vector3{0, -2, 0});

    // primitive mesh 4
    Primitive *prim4 = scene->Instantiate(
        new Primitive(PrimitiveType::SphereMesh, pMat),
        Vector3{5, 7, 0});
    prim4->rigidbody->AddForce(Vector3{-.5, -.5, 0});

    // suzane
    SceneObject *suzane = scene->Instantiate<SceneObject>(new SceneObject(), Vector3{2, 0, 1});
    suzane->AddComponent<Mesh>(Mesh::LoadMeshFromFile(
        "meshes/suzane.obj",
        new M_Lit(Texture::LoadTexture("textures/UVGrid.png"))));

    app->Run();

    app->terminate();
    return 0;
}

#pragma endregion
