#include "diagnostics.h"
#include "application.h"
#include "core.h"
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
    CondorEngine::SceneObject* shape = scene.Instanciate(new CondorEngine::SceneObject());
    CondorEngine::Component* meshComp = shape->AddComponent(CondorEngine::Mesh::LoadMeshFromFile("meshes/suzane.obj"));

    // Camera
    CondorEngine::Camera::Init(vec3{ 0, 0, 3 }, vec3{ 0,0,0, });


#pragma region Basic Render
    // Shaders
    //CondorEngine::Shader basicShader = CondorEngine::Shader::LoadDiffuseShader();
    //Shader basicShader = Primitive::LoadNormalShader();

    // Geometry
    CondorEngine::Primitive cube = CondorEngine::Primitive(CondorEngine::PrimitiveType::Cube);
    mat4 modelTransform = glm::identity<mat4>();
    modelTransform = glm::scale(modelTransform, vec3{ .1f,.1f,.1f});
    CondorEngine::Texture sampleTex = *CondorEngine::Texture::LoadTexture("textures/wet_koala.jpg");
    CondorEngine::Mesh mesh = *CondorEngine::Mesh::LoadMeshFromFile("meshes/Bunny.obj");

    // Lights
    /*Light light = {
        vec3{1,1,1}, // color
        vec3{-.803046f, -0.0f, -.595917f} }; // direction
    vec3 AmbientLightColor = { .1,.1,.1 };

    // Uniforms
    SetUniform(basicShader, 0, Camera::Instance()->projectionMatrix);
    SetUniform(basicShader, 1, Camera::Instance()->viewMatrix);
    SetUniform(basicShader, 2, modelTransform);
    SetUniform(basicShader, 3, sampleTex, 0);
    SetUniform(basicShader, 4, AmbientLightColor);
    SetUniform(basicShader, 5, light.color);
    SetUniform(basicShader, 6, light.direction);
    SetUniform(basicShader, 7, Camera::Instance()->position);*/
    

#pragma endregion

    while (!app.shouldClose()) {
        app.tick();
        app.clear();
        app.update();
        app.lateUpdate();

        /*modelTransform = glm::rotate(modelTransform, 0.01f, vec3{0,1,0});
        SetUniform(basicShader, 2, modelTransform);
        //DrawGeometry(basicShader, face);

        DrawGeometry(basicShader, mesh);*/
    }

    app.terminate();
    return 0;
}
