#include <CondorEngine.hpp>
#include <CondorEngine/scenes/defaultscene.h>
#include <CondorEngine/sceneobjects/primitive.h>

using namespace CondorEngine;

#pragma region Main

int main()
{
    Application *app = Application::Instance();
    if (!app->init(640, 480, "CondorEngine"))
    {
        Debug::LogError("Failed to initialise application.");
        return -1;
    }
    Time::fixedTimeStep = .02f;

    diagnostics::Environment();

    // Scene
    Scene *scene = Application::activeScene = new DefaultScene();

    // material
    M_Lit *pMat = new M_Lit(Texture::LoadTexture("textures/ColorGrid.png"));

    // primitive meshes
    Primitive *prim = scene->Instantiate(
        new Primitive(PrimitiveType::CubeMesh, pMat),
        Vector3{0, .5f, 0});
    Primitive *prim2 = scene->Instantiate(
        new Primitive(PrimitiveType::SphereMesh, pMat),
        Vector3{0, 0, 0});
    Primitive *prim3 = scene->Instantiate(
        new Primitive(PrimitiveType::SphereMesh, pMat),
        Vector3{0, -2, 0});
    Primitive *prim4 = scene->Instantiate(
        new Primitive(PrimitiveType::SphereMesh, pMat),
        Vector3{5, 7, 0});
    prim4->rigidbody->AddForce(Vector3{-.5, -.5, 0});
    Primitive *prim5 = scene->Instantiate(
        new Primitive(PrimitiveType::PlaneMesh),
        Vector3{-2, 1.5, 0});
    prim5->Rotate(Vector3{0, 0, -90});
    Primitive *prim6 = scene->Instantiate(
        new Primitive(PrimitiveType::PlaneMesh),
        Vector3{6, 1.5, 0});
    prim6->Rotate(Vector3{0, 0, 90});

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
