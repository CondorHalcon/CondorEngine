#include "diagnostics.h"
#include "math.h"
#include "core.h"
#include "application.h"
#include "renderer.h"
#include "debug.h"
#include "sceneobjects/spectatorcam.h"
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
    CondorEngine::Scene* scene = Application::activeScene = new CondorEngine::Scene();
    // Camera
    CondorEngine::SpectatorCam *camera = scene->Instantiate<CondorEngine::SpectatorCam>(new CondorEngine::SpectatorCam());

    // imported mesh
    CondorEngine::Mesh* meshComp = CondorEngine::Mesh::LoadMeshFromFile("meshes/suzane.obj");
    meshComp->material = new CondorEngine::M_Lit();
    Rotatable* shape = scene->Instantiate<Rotatable>(new Rotatable(meshComp));

    // primitive mesh
    scene->Instantiate(new CondorEngine::Primitive(CondorEngine::SimpleCube));
    

    while (!app->shouldClose()) {
        app->tick();
        app->clear();
        app->update();
        app->lateUpdate();
    }

    app->terminate();
    return 0;
}
