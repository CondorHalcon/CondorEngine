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
#include "sceneobjects/spectatorcam.h"
#include "sceneobjects/primitive.h"
#include "components/mesh.h"
#include "components/rigidbody.h"
// std
#include <iostream>
#include <string>

using namespace CondorEngine;

#pragma region Implementation Classes

/// @brief 
class Rotatable : public SceneObject {
public:
    Rotatable() : SceneObject() {
        this->name = "Rotatable";
        this->mesh = nullptr;
    }
    Rotatable(Mesh* mesh) : SceneObject() {
        this->name = "Rotatable";
        this->mesh = AddComponent<Mesh>(mesh);
    }
    Mesh* mesh;
    bool control = true;
    float rotationSpeed = 10;
    void Update() override {
        if (control) {// rotate up down
            if (Application::Input(GLFW_KEY_UP)) {
                Rotate(Vector3{ 1, 0, 0 } * rotationSpeed * Time::deltaTime());
            }
            if (Application::Input(GLFW_KEY_DOWN)) {
                Rotate(Vector3{ -1, 0, 0 } * rotationSpeed * Time::deltaTime());
            }
            // rotate left right
            if (Application::Input(GLFW_KEY_RIGHT)) {
                Rotate(Vector3{ 0, -1, 0 } * rotationSpeed * Time::deltaTime());
            }
            if (Application::Input(GLFW_KEY_LEFT)) {
                Rotate(Vector3{ 0, 1, 0 } * rotationSpeed * Time::deltaTime());
            }
        }
    }
};
class FixedTimePrinter : public SceneObject {
    public:
    FixedTimePrinter() : SceneObject() {}
    void FixedUpdate() override {
        Debug::Log("FixedTime: time: " +
            std::to_string(Time::time()) + 
            "; deltaTime: " + std::to_string(Time::deltaTime()) + 
            "; fixedTimeStep: " + std::to_string(Time::fixedTimeStep) +
            "; fixedDeltaTime: " + std::to_string(Time::fixedDeltaTime())
        );
    }
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
    Scene* scene = Application::activeScene = new Scene();

    // Camera
    SpectatorCam* camera = scene->Instantiate<SpectatorCam>(new SpectatorCam(), Vector3{0, 0, 5});
    camera->Rotate(Vector3{0, 180, 0});

    // simple SceneObject
    //M_Lit* sMat = new M_ComplexLit();
    //sMat->sampleTex = Texture::LoadTexture("textures/wet_koala.jpg");
    //SceneObject* shape = scene->Instantiate<SceneObject>(new SceneObject());
    //Mesh* shapeMesh = shape->AddComponent<Mesh>(Mesh::LoadMeshFromFile("meshes/suzane.obj", sMat));
    //shape->Move(Vector3{-2, 0, 1});
    //shape->Rotate(Vector3{ 0,90,0 });

    // material
    M_Lit* pMat = new M_Lit(Texture::LoadTexture("textures/ColorGrid.png"));
    M_Lit* pMat2 = new M_Lit();

    // primitive mesh
    Primitive* prim = scene->Instantiate(
        new Primitive(PrimitiveType::CubeMesh, pMat), 
        Vector3{-2.8, 2, 0});
    prim->rigidbody->AddForce(Vector3{1, -1, 0} * .1f);

    // primitive mesh 2
    Primitive* prim2 = scene->Instantiate(
        new Primitive(PrimitiveType::SphereMesh, pMat), 
        Vector3{0, 0, 0});

    // primitive mesh 3
    Primitive *prim3 = scene->Instantiate(
        new Primitive(PrimitiveType::PlaneMesh, pMat2), 
        Vector3{0, -1, 0});

    // rotatable
    Rotatable* rotatable = scene->Instantiate<Rotatable>(new Rotatable(), Vector3{ 2, 0, 1 });
    rotatable->mesh = rotatable->AddComponent<Mesh>(
        Mesh::LoadMeshFromFile("meshes/suzane.obj", 
        new M_Lit(Texture::LoadTexture("textures/UVGrid.png"))));
    rotatable->control = false;

    //Debug::Log("fixedTimeStep " + std::to_string(Time::fixedTimeStep));
    //Time::fixedTimeStep = 1.0f;
    //Debug::Log("fixedTimeStep " + std::to_string(Time::fixedTimeStep));
    //FixedTimePrinter* timePrinter = scene->Instantiate<FixedTimePrinter>(new FixedTimePrinter());

    app->Run();

    app->terminate();
    return 0;
}

#pragma endregion
