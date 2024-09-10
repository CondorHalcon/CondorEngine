#include "diagnostics.h"
#include "core.h"
#include "application.h"
#include "renderer.h"
#include "camera.h"
#include "sceneobjects/primitive.h"
#include "components/mesh.h"
// std
#include <iostream>
// third party
#include "glm/ext.hpp"
#include "glfw/glfw3.h"
using glm::mat4;
using glm::vec3;

#pragma region Implimentaion Classes

class ShapeMaterial : public CondorEngine::Material {
public:
    ShapeMaterial(CondorEngine::Shader* shader) : Material(shader) { 
        sampleTex = CondorEngine::Texture::LoadTexture("textures/wet_koala.jpg");
    }

    CondorEngine::Texture* sampleTex;

    void Update() override {
        Material::Update();
        SetUniform(3, *sampleTex, 0);
        SetUniform(4, Application::activeScene->ambientLight);
        SetUniform(5, Application::activeScene->light->color);
        SetUniform(6, Application::activeScene->light->direction);
        SetUniform(7, CondorEngine::Camera::Instance()->position);
    }
};
#pragma endregion

int main()
{
    const unsigned windowWidth = 640;
    const unsigned windowHeight = 480;
    Application app;
    app.init(windowWidth, windowHeight, "CondorEngine");

    CondorEngine::diagnostics::Environment();

    // Scene
    Application::activeScene = new CondorEngine::Scene();
    CondorEngine::Scene scene;
    // Camera
    CondorEngine::Camera::Init(vec3{ 0, 0, 3 }, vec3{ 0,0,0, });

    // imported mesh
    CondorEngine::SceneObject* shape = scene.Instanciate(new CondorEngine::SceneObject());
    CondorEngine::Mesh* meshComp = CondorEngine::Mesh::LoadMeshFromFile("meshes/suzane.obj");
    meshComp->material = new CondorEngine::M_Lit();
    shape->AddComponent(meshComp);
    Application::activeScene->hiearchy.push_back(shape);

    // primitive mesh
    CondorEngine::Primitive* prim = scene.Instanciate(new CondorEngine::Primitive(CondorEngine::SimpleCube));
    //CondorEngine::Primitive* cube = new CondorEngine::Primitive(CondorEngine::PrimitiveType::Cube);
    //Application::activeScene->hiearchy.push_back(cube);

    mat4 transform = glm::identity<mat4>();
    

    while (!app.shouldClose()) {
        app.tick();
        app.clear();
        app.update();
        app.lateUpdate();
        app.lateUpdate();
    }

    app.terminate();
    return 0;
}
