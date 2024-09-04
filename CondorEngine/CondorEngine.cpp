#include "diagnostics.h"
#include "context.h"
#include "core.h"
#include "renderer.h"
#include "primitive.h"
#include "camera.h"
#include "importer.h"
// external
#include <iostream>
#include "glm/ext.hpp"
#include "glfw/glfw3.h"
using glm::mat4;
using glm::vec3;

#pragma region Implimentaion Classes

class ShapeMesh : public CondorEngine::Mesh {
public:
    ShapeMesh(Shape* shape) : Mesh(shape) {
        sampleTex = &LoadTexture("textures/wet_koala.jpg");
    }
public:
    Texture* sampleTex;
public:
    void PreDraw() override {
        Mesh::PreDraw();

        SetUniform(*getShader(), 3, *sampleTex, 0);
        SetUniform(*getShader(), 4, getSceneObject()->getScene()->ambientLight);
        SetUniform(*getShader(), 5, getSceneObject()->getScene()->light->color);
        SetUniform(*getShader(), 6, getSceneObject()->getScene()->light->direction);
        SetUniform(*getShader(), 7, Camera::Instance()->position);
    }
};
#pragma endregion

int main()
{
    const unsigned windowWidth = 640;
    const unsigned windowHeight = 480;
    Context context;
    context.init(windowWidth, windowHeight, "CondorEngine");

    CondorEngine::diagnostics::Environment();

    // Scene
    CondorEngine::Scene scene;
    CondorEngine::SceneObject* shape = scene.Instanciate(new CondorEngine::SceneObject());
    CondorEngine::Component* meshComp = shape->AddComponent(CondorEngine::Mesh::LoadMeshFromFile())

    // Camera
    Camera::Init(vec3{ 0, 0, 3 }, vec3{ 0,0,0, });


#pragma region Basic Render
    // Shaders
    Shader basicShader = Primitive::LoadDiffuseShader();
    //Shader basicShader = Primitive::LoadNormalShader();

    // Geometry
    //Geometry face = Primitive::MakeCube();
    mat4 modelTransform = glm::identity<mat4>();
    modelTransform = glm::scale(modelTransform, vec3{ .1f,.1f,.1f});
    Texture sampleTex = LoadTexture("textures/wet_koala.jpg");
    Geometry mesh = MakeGeometryFromFile("meshes/Bunny.obj");

    // Lights
    Light light = {
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
    SetUniform(basicShader, 7, Camera::Instance()->position);
    

#pragma endregion

    while (!context.shouldClose()) {
        context.tick();
        context.clear();

        modelTransform = glm::rotate(modelTransform, 0.01f, vec3{ 0,1,0 });
        SetUniform(basicShader, 2, modelTransform);
        //DrawGeometry(basicShader, face);

        DrawGeometry(basicShader, mesh);
    }

    context.terminate();
    return 0;
}
