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
    camera->Move(CondorEngine::Vector3{ 0,0,5 });
    camera->Rotate(CondorEngine::Vector3{0, 180, 0});

    // simple SceneObject
    CondorEngine::SceneObject* shape = scene->Instantiate<CondorEngine::SceneObject>(new CondorEngine::SceneObject());
    CondorEngine::Mesh* shapeMesh = shape->AddComponent<CondorEngine::Mesh>(CondorEngine::Mesh::LoadMeshFromFile("meshes/suzane.obj"));
    shape->Move(CondorEngine::Vector3{-2, 0, 1});
    shape->Rotate(CondorEngine::Vector3{ 0,90,0 });

    // primitive mesh
    CondorEngine::Primitive* primitive = scene->Instantiate(new CondorEngine::Primitive(CondorEngine::Cube));
    primitive->Move(CondorEngine::Vector3{3, 1, 0});
    delete primitive->mesh->material;
    CondorEngine::M_Lit* texMat = new CondorEngine::M_Lit();
    texMat->sampleTex = CondorEngine::Texture::LoadTexture("textures/wet_koala.jpg");
    primitive->mesh->material = texMat;

    // rotatable
    Rotatable* rotatable = scene->Instantiate<Rotatable>(new Rotatable());
    rotatable->mesh = rotatable->AddComponent<CondorEngine::Mesh>(CondorEngine::Mesh::LoadMeshFromFile("meshes/suzane.obj"));

    while (!app->shouldClose()) {
        app->tick();
        app->clear();
        app->update();
        app->lateUpdate();
    }

    app->terminate();
    return 0;
}
