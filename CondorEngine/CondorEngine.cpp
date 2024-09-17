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
    Rotatable() : SceneObject() {
        this->name = "Rotatable";
        this->mesh = nullptr;
    }
    Rotatable(CondorEngine::Mesh* mesh) : SceneObject() {
        this->name = "Rotatable";
        this->mesh = AddComponent<CondorEngine::Mesh>(mesh);
    }
    CondorEngine::Mesh* mesh;
    void Update() override {
        /*CondorEngine::Debug::Log(
            "forward: " + CondorEngine::to_string(getForward()) +
            "; right: " + CondorEngine::to_string(getRight()) +
            "; up: " + CondorEngine::to_string(getUp())
        );*/
        // move forwad back
        if (Application::Input(GLFW_KEY_W)) {
            Move(getForward() * .01f);
        }
        if (Application::Input(GLFW_KEY_S)) {
            Move(getForward() * -.01f);
        }
        // move right left
        if (Application::Input(GLFW_KEY_D)) {
            Move(getRight() * .01f);
        }
        if (Application::Input(GLFW_KEY_A)) {
            Move(getRight() * -.01f);
        }
        // move up down
        if (Application::Input(GLFW_KEY_E)) {
            Move(getUp() * .01f);
        }
        if (Application::Input(GLFW_KEY_Q)) {
            Move(getUp() * -.01f);
        }
        // rotate up down
        if (Application::Input(GLFW_KEY_UP)) {
            Rotate(CondorEngine::Vector3{ .2, 0, 0 });
        }
        if (Application::Input(GLFW_KEY_DOWN)) {
            Rotate(CondorEngine::Vector3{ -.2, 0, 0 });
        }
        // rotate left right
        if (Application::Input(GLFW_KEY_RIGHT)) {
            Rotate(CondorEngine::Vector3{ 0, -.2, 0 });
        }
        if (Application::Input(GLFW_KEY_LEFT)) {
            Rotate(CondorEngine::Vector3{ 0, .2, 0 });
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
    camera->Move(CondorEngine::Vector3{ 0,0,-3 });
    camera->enabled = false;

    // imported mesh
    Rotatable* shape = scene->Instantiate<Rotatable>(new Rotatable());
    shape->mesh = shape->AddComponent<CondorEngine::Mesh>(CondorEngine::Mesh::LoadMeshFromFile("meshes/suzane.obj"));
    //CondorEngine::SceneObject* shape = scene->Instantiate<CondorEngine::SceneObject>(new CondorEngine::SceneObject());
    //shape->AddComponent<CondorEngine::Mesh>(CondorEngine::Mesh::LoadMeshFromFile("meshes/suzane.obj"));
    CondorEngine::Debug::Log(
        "forward: " + CondorEngine::to_string(shape->getForward()) +
        "; right: " + CondorEngine::to_string(shape->getRight()) +
        "; up: " + CondorEngine::to_string(shape->getUp())
    );
    shape->Rotate(CondorEngine::Vector3{ 0,90,0 });
    CondorEngine::Debug::Log(
        "forward: " + CondorEngine::to_string(shape->getForward()) +
        "; right: " + CondorEngine::to_string(shape->getRight()) +
        "; up: " + CondorEngine::to_string(shape->getUp())
    );

    // primitive mesh
    CondorEngine::Primitive* primitive = scene->Instantiate(new CondorEngine::Primitive(CondorEngine::SimpleCube));
    primitive->mesh->material = new CondorEngine::M_Normal();
    

    while (!app->shouldClose()) {
        app->tick();
        app->clear();
        app->update();
        app->lateUpdate();
    }

    app->terminate();
    return 0;
}
