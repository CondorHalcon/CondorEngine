#include "diagnostics.h"
#include "core.h"
#include "application.h"
#include "renderer.h"
#include "camera.h"
#include "debug.h"
#include "sceneobjects/primitive.h"
#include "components/mesh.h"
// std
#include <iostream>
#include <string>
// third party
#include "glm/ext.hpp"
#include "glfw/glfw3.h"

#pragma region Implementation Classes

class Rotatable : public CondorEngine::SceneObject {
public:
    Rotatable(CondorEngine::Mesh* mesh) : SceneObject() {
        this->mesh = AddComponent<CondorEngine::Mesh>(mesh);
    }
    CondorEngine::Mesh* mesh;
    void Update() override {
        if (Application::Input(GLFW_KEY_W)) {
            transform = glm::rotate(transform, .01f, CondorEngine::Vector3{ -1, 0, 0 });
        }
        if (Application::Input(GLFW_KEY_A)) {
            transform = glm::rotate(transform, .01f, CondorEngine::Vector3{ 0, -1, 0 });
        }
        if (Application::Input(GLFW_KEY_S)) {
            transform = glm::rotate(transform, .01f, CondorEngine::Vector3{ 1, 0, 0 });
        }
        if (Application::Input(GLFW_KEY_D)) {
            transform = glm::rotate(transform, .01f, CondorEngine::Vector3{ 0, 1, 0 });
        }
    }
};

#pragma endregion

int main()
{
    const unsigned windowWidth = 640;
    const unsigned windowHeight = 480;
    Application* app = Application::Instance();
    app->init(windowWidth, windowHeight, "CondorEngine");

    CondorEngine::diagnostics::Environment();

    // Scene
    Application::activeScene = new CondorEngine::Scene();
    CondorEngine::Scene scene;
    // Camera
    CondorEngine::Camera::Init(CondorEngine::Vector3{ 0, 0, 3 }, CondorEngine::Vector3{ 0,0,0, });

    // imported mesh
    CondorEngine::Mesh* meshComp = CondorEngine::Mesh::LoadMeshFromFile("meshes/suzane.obj");
    meshComp->material = new CondorEngine::M_Lit();
    Rotatable* shape = scene.Instantiate<Rotatable>(new Rotatable(meshComp));
    //Application::activeScene->hierarchy.push_back(shape);

    // primitive mesh
    //CondorEngine::Primitive* prim = scene.Instantiate(new CondorEngine::Primitive(CondorEngine::SimpleCube));

    CondorEngine::Transform transform = glm::identity<CondorEngine::Transform>();
    

    while (!app->shouldClose()) {
        app->tick();
        app->clear();
        app->update();
        app->lateUpdate();
        app->lateUpdate();
    }

    app->terminate();
    return 0;
}
