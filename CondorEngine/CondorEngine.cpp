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
using glm::mat4;
using glm::vec3;

#pragma region Implimentaion Classes

class Rotatable : public CondorEngine::SceneObject {
public:
    Rotatable(CondorEngine::Mesh* mesh) : SceneObject() {
        this->mesh = AddComponent(mesh);
    }
    CondorEngine::Mesh* mesh;
    void Update() override {
        if (Application::Input(GLFW_KEY_W)) {
            transform = glm::rotate(transform, .01f, vec3{ -1, 0, 0 });
        }
        if (Application::Input(GLFW_KEY_A)) {
            transform = glm::rotate(transform, .01f, vec3{ 0, -1, 0 });
        }
        if (Application::Input(GLFW_KEY_S)) {
            transform = glm::rotate(transform, .01f, vec3{ 1, 0, 0 });
        }
        if (Application::Input(GLFW_KEY_D)) {
            transform = glm::rotate(transform, .01f, vec3{ 0, 1, 0 });
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
    CondorEngine::Camera::Init(vec3{ 0, 0, 3 }, vec3{ 0,0,0, });

    // imported mesh
    CondorEngine::Mesh* meshComp = CondorEngine::Mesh::LoadMeshFromFile("meshes/suzane.obj");
    meshComp->material = new CondorEngine::M_Lit();
    Rotatable* shape = scene.Instanciate(new Rotatable(meshComp));
    Application::activeScene->hiearchy.push_back(shape);

    // primitive mesh
    //CondorEngine::Primitive* prim = scene.Instanciate(new CondorEngine::Primitive(CondorEngine::SimpleCube));

    mat4 transform = glm::identity<mat4>();
    

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
