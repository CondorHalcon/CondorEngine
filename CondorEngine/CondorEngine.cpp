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
    float rotationSpeed = 10;
    void Update() override {
        if (control) {// rotate up down
            if (Application::Input(GLFW_KEY_UP)) {
                Rotate(CondorEngine::Vector3{ 1, 0, 0 } * rotationSpeed * CondorEngine::Time::deltaTime());
            }
            if (Application::Input(GLFW_KEY_DOWN)) {
                Rotate(CondorEngine::Vector3{ -1, 0, 0 } * rotationSpeed * CondorEngine::Time::deltaTime());
            }
            // rotate left right
            if (Application::Input(GLFW_KEY_RIGHT)) {
                Rotate(CondorEngine::Vector3{ 0, -1, 0 } * rotationSpeed * CondorEngine::Time::deltaTime());
            }
            if (Application::Input(GLFW_KEY_LEFT)) {
                Rotate(CondorEngine::Vector3{ 0, 1, 0 } * rotationSpeed * CondorEngine::Time::deltaTime());
            }
        }
    }
};
class FixedTimePrinter : public CondorEngine::SceneObject {
    public:
    FixedTimePrinter() : SceneObject() {}
    void FixedUpdate() override {
        CondorEngine::Debug::Log("FixedTime: time: " +
            std::to_string(CondorEngine::Time::time()) + 
            "; deltaTime: " + std::to_string(CondorEngine::Time::deltaTime()) + 
            "; fixedTimeStep: " + std::to_string(CondorEngine::Time::fixedTimeStep) +
            "; fixedDeltaTime: " + std::to_string(CondorEngine::Time::fixedDeltaTime())
        );
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

    // simple SceneObject
    //CondorEngine::M_Lit* sMat = new CondorEngine::M_ComplexLit();
    //sMat->sampleTex = CondorEngine::Texture::LoadTexture("textures/wet_koala.jpg");
    //CondorEngine::SceneObject* shape = scene->Instantiate<CondorEngine::SceneObject>(new CondorEngine::SceneObject());
    //CondorEngine::Mesh* shapeMesh = shape->AddComponent<CondorEngine::Mesh>(CondorEngine::Mesh::LoadMeshFromFile("meshes/suzane.obj", sMat));
    //shape->Move(CondorEngine::Vector3{-2, 0, 1});
    //shape->Rotate(CondorEngine::Vector3{ 0,90,0 });

    // koala material
    CondorEngine::M_Lit* pMat = new CondorEngine::M_Lit();
    pMat->sampleTex = CondorEngine::Texture::LoadTexture("textures/wet_koala.jpg");

    // primitive mesh
    CondorEngine::Primitive* prim = scene->Instantiate(
        new CondorEngine::Primitive(CondorEngine::PrimitiveType::SphereMesh, pMat), 
        CondorEngine::Vector3{-2, 2, 0});
    prim->rigidbody->AddForce(CondorEngine::Vector3{1, -1, 0} * .1f);

    // primitive mesh 2
    /*CondorEngine::Primitive* prim2 = scene->Instantiate(
        new CondorEngine::Primitive(CondorEngine::PrimitiveType::SphereMesh, pMat), 
        CondorEngine::Vector3{0, 0, 0});*/

    // primitive mesh 3
    CondorEngine::Primitive *prim3 = scene->Instantiate(
        new CondorEngine::Primitive(CondorEngine::PrimitiveType::PlaneMesh, pMat), 
        CondorEngine::Vector3{0, -1.5, 0});

    // rotatable
    Rotatable* rotatable = scene->Instantiate<Rotatable>(new Rotatable(), CondorEngine::Vector3{ 2, 0, 1 });
    rotatable->mesh = rotatable->AddComponent<CondorEngine::Mesh>(CondorEngine::Mesh::LoadMeshFromFile("meshes/suzane.obj", new CondorEngine::M_Lit()));
    rotatable->control = false;

    //CondorEngine::Debug::Log("fixedTimeStep " + std::to_string(CondorEngine::Time::fixedTimeStep));
    //CondorEngine::Time::fixedTimeStep = 1.0f;
    //CondorEngine::Debug::Log("fixedTimeStep " + std::to_string(CondorEngine::Time::fixedTimeStep));
    //FixedTimePrinter* timePrinter = scene->Instantiate<FixedTimePrinter>(new FixedTimePrinter());

    app->Run();

    app->terminate();
    return 0;
}

#pragma endregion
