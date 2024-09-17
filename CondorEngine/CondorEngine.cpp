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
            Rotate(CondorEngine::Vector3{ -.01, 0, 0 });
        }
        if (Application::Input(GLFW_KEY_A)) {
            Rotate(CondorEngine::Vector3{ 0, -.01, 0 });
        }
        if (Application::Input(GLFW_KEY_S)) {
            Rotate(CondorEngine::Vector3{ .01, 0, 0 });
        }
        if (Application::Input(GLFW_KEY_D)) {
            Rotate(CondorEngine::Vector3{ 0, .01, 0 });
        }
    }
};

#pragma endregion

int main()
{
    Application* app = Application::Instance();
    app->init(640, 480, "CondorEngine");

    CondorEngine::diagnostics::Environment();

    // Scene
    CondorEngine::Scene* scene = Application::activeScene = new CondorEngine::Scene();
    // Camera
    CondorEngine::SpectatorCam *camera = scene->Instantiate<CondorEngine::SpectatorCam>(new CondorEngine::SpectatorCam());
    camera->Move(CondorEngine::Vector3{ 0,0,3 });

    // imported mesh
    //Rotatable* shape = scene->Instantiate<Rotatable>(new Rotatable(meshComp));
    CondorEngine::SceneObject* shape = scene->Instantiate<CondorEngine::SceneObject>(new CondorEngine::SceneObject());
    CondorEngine::Mesh* meshComp = shape->AddComponent(CondorEngine::Mesh::LoadMeshFromFile("meshes/suzane.obj"));
    meshComp->material = new CondorEngine::M_Lit();

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
