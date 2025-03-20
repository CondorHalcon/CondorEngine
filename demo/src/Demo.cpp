#include <CondorEngine.hpp>
#include <CondorEngine/scenes/defaultscene.h>
#include <CondorEngine/sceneobjects/primitive.h>
#include <CondorEngine/sceneobjects/suzane.h>
#include <CondorEngine/sceneobjects/scenelight.h>
#include <stdexcept>
#include <cstdlib>

using namespace CondorEngine;

class DemoScene : public DefaultScene
{
public:
    DemoScene() {
        light = DirectionalLight(ColorRGB{ .7, .7, .7 }, Vector3{ 0, -.3, -.7 });
        Instantiate<SceneLight>(new SceneLight(ColorRGB{ 1, 0, 0 }), Vector3{ -4, 0, 0 });
        Instantiate<SceneLight>(new SceneLight(ColorRGB{ 0, 0, 1 }), Vector3{ 4, 0, 0 });

        Texture uvGrid = ResourceManager::LoadTexture("textures/UVGrid.png");
        Phong* pMat = new Phong(ResourceManager::LoadTexture("textures/ColorGrid.png"));

        // primitive meshes
        Instantiate(new Primitive(PrimitiveType::CubeMesh, pMat), Vector3{ 0, .5f, -6 });
        Instantiate(new Primitive(PrimitiveType::SphereMesh, pMat), Vector3{ 0, 0, -6 });
        Instantiate(new Primitive(PrimitiveType::SphereMesh, new Unlit(uvGrid)), Vector3{ 0, -2, -6 });
        Primitive* prim4 = Instantiate(new Primitive(PrimitiveType::SphereMesh, new Normal()), Vector3{ 5, 7, -6 });
        prim4->rigidbody->AddForce(Vector3{ -.5, -.5, 0 });
        Primitive* prim5 = Instantiate(new Primitive(PrimitiveType::PlaneMesh), Vector3{ -2, 1.5, -6 });
        prim5->Rotate(Vector3{ 0, 0, -90 });
        Primitive* prim6 = Instantiate(new Primitive(PrimitiveType::PlaneMesh), Vector3{ 6, 1.5, -6 });
        prim6->Rotate(Vector3{ 0, 0, 90 });

        // suzane
        Instantiate<Suzane>(new Suzane(new Phong()), Vector3{ 6, 0, -3 });
        Instantiate<Suzane>(new Suzane(), Vector3{ 2, 0, -3 });
        Instantiate<Suzane>(new Suzane(new Diffuse()), Vector3{ -2, 0, -3 });
        Instantiate<Suzane>(new Suzane(new Diffuse(uvGrid)), Vector3{ -6, 0, -3 });
        Instantiate(new Suzane(new Normal()), Vector3{ 6, 2, -3 });
        Instantiate(new Suzane(new Unlit(uvGrid)), Vector3{ 2, 2, -3 });
        Instantiate(new Suzane(new Unlit()), Vector3{ -2, 2, -3 });
        Instantiate(new Suzane(new UV()), Vector3{ -6, 2, -3 });

        Material* multiLightMat = new Phong();
        Instantiate(new Primitive(PrimitiveType::SphereMesh, multiLightMat), Vector3{ 2, -2, 0 });
        Instantiate(new Suzane(multiLightMat), Vector3{ -2, -2, 0 });
    }
};

#pragma region Main

int main()
{
    Application *app = Application::Instance();
    try {
        if (!app->init(1280, 720, "CondorEngine"))
        {
            throw std::runtime_error("Failed to initialise application.");
            return -1;
        }

        // Scene
        Scene* scene = new DemoScene();
        Application::activeScene = scene;

        app->runtime();
    }
    catch (const std::exception& e) {
        Debug::LogError(e.what());
        return EXIT_FAILURE;
    }

    app->terminate();
    return EXIT_SUCCESS;
}

#pragma endregion
