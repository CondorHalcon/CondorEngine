// third party
#include "glew/glew.h"
#include "glm/ext.hpp"
#include "glfw/glfw3.h"
// internal
#include "diagnostics.h"
#include "math.h"
#include "core.h"
#include "application.h"
#include "renderer.h"
#include "debug.h"
#include "sceneobjects/scenelight.h"
#include "sceneobjects/spectatorcam.h"
#include "sceneobjects/primitive.h"
#include "components/mesh.h"
#include "time.h"
// std
#include <iostream>
#include <string>

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
    bool control = true;
    void Update() override {
        if (control) {// rotate up down
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
    }
};
class M_Test : public CondorEngine::Material {
public:
    static const unsigned COUNT = 2;
    M_Test() : Material(CondorEngine::Shader::LoadShader("shaders/directional.vert", "shaders/test.frag")) { }
    void Update() override {
        Material::Update();
        CondorEngine::ColorRGB colors[COUNT];
        colors[0] = CondorEngine::ColorRGB{1, 0, 0};
        colors[1] = CondorEngine::ColorRGB{0, 1, 0};
        SetUniform(3, COUNT, *colors);
    }
};
class FixedTimePrinter : public CondorEngine::SceneObject {
    public:
    FixedTimePrinter() : SceneObject() {}
    void FixedUpdate() override {
        CondorEngine::Debug::Log(std::to_string(CondorEngine::time()));
    }
};

#pragma endregion

#pragma region Main

int main()
{
    Application* app = Application::Instance();
    app->init(640, 480, "CondorEngine");

    CondorEngine::diagnostics::Environment();

    // Scene
    CondorEngine::Scene* scene = Application::activeScene = new CondorEngine::Scene();

    // Camera
    CondorEngine::SpectatorCam* camera = scene->Instantiate<CondorEngine::SpectatorCam>(new CondorEngine::SpectatorCam());
    camera->Move(CondorEngine::Vector3{ 0,0,5 });
    camera->Rotate(CondorEngine::Vector3{0, 180, 0});

    // second light
    CondorEngine::SceneLight *light = scene->Instantiate<CondorEngine::SceneLight>(new CondorEngine::SceneLight(
        CondorEngine::ColorRGB{.5, .5, .5}, CondorEngine::Vector3{-.7, -.7, 0}));

    // simple SceneObject
    CondorEngine::M_Lit* sMat = new CondorEngine::M_ComplexLit();
    sMat->sampleTex = CondorEngine::Texture::LoadTexture("textures/wet_koala.jpg");
    CondorEngine::SceneObject* shape = scene->Instantiate<CondorEngine::SceneObject>(new CondorEngine::SceneObject());
    CondorEngine::Mesh* shapeMesh = shape->AddComponent<CondorEngine::Mesh>(CondorEngine::Mesh::LoadMeshFromFile("meshes/suzane.obj", sMat));
    shape->Move(CondorEngine::Vector3{-2, 0, 1});
    shape->Rotate(CondorEngine::Vector3{ 0,90,0 });

    // primitive mesh
    CondorEngine::M_Lit* pMat = new CondorEngine::M_Lit();
    pMat->sampleTex = CondorEngine::Texture::LoadTexture("textures/wet_koala.jpg");
    CondorEngine::Primitive* primitive = scene->Instantiate(new CondorEngine::Primitive(CondorEngine::PrimitiveType::Plane, pMat));
    primitive->Move(CondorEngine::Vector3{0, -1, 0});
    //primitive->Rotate(CondorEngine::Vector3{ 15, 45, 0 });

    // rotatable
    Rotatable* rotatable = scene->Instantiate<Rotatable>(new Rotatable());
    rotatable->mesh = rotatable->AddComponent<CondorEngine::Mesh>(CondorEngine::Mesh::LoadMeshFromFile("meshes/suzane.obj", new CondorEngine::M_Lit()));
    rotatable->Move(CondorEngine::Vector3{ 2, 0, 1 });

    CondorEngine::fixedTimeStep = 1.0;
    FixedTimePrinter* timePrinter = scene->Instantiate<FixedTimePrinter>(new FixedTimePrinter());

    app->Run();

    app->terminate();
    return 0;
}

#pragma endregion
