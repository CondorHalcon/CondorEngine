//#include <iostream>
#include "diagnostics.h"
#include "context.h"
#include "renderer.h"
// external
#include "glm/ext.hpp"
#include "glfw/glfw3.h"
using glm::mat4;
using glm::vec3;

int main()
{
    const unsigned windowWidth = 640;
    const unsigned windowHeight = 480;
    Context context;
    context.init(windowWidth, windowHeight, "CondorEngine");

    diagnostics::Environment();

#pragma region Basic Render

    // Mesh
    Vertex verts[] =
    {
        { // 0: vertex
            vec4{-.5f, -.5f, .5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{0.0f,0.0f}, // vertex uv
            vec3{-.7f,-.7f,.7f}  // vertex normal
        },
        { // 1: vertex
            vec4{.5f, -.5f, .5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{1.0f,0.0f}, // vertex uv
            vec3{.7f,-.7f,.7f}  // vertex normal
        },
        { // 2: vertex
            vec4{-.5f, .5f, .5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{0.0f,1.0f}, // vertex uv
            vec3{-.7f,.7f,.7f}  // vertex normal
        },
        { // 3: vertex
            vec4{.5f, .5f, .5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{1.0f,1.0f}, // vertex uv
            vec3{.7f,.7f,.7f}  // vertex normal
        },
        { // 4: vertex
            vec4{-.5f, -.5f, -.5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{-1.0f,0.0f}, // vertex uv
            vec3{-.7f,-.7f,-.7f}  // vertex normal
        },
        { // 5: vertex
            vec4{.5f, -.5f, -.5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{0.0,0.0f}, // vertex uv
            vec3{.7f,-.7f,-.7f}  // vertex normal
        },
        { // 6: vertex
            vec4{-.5f, .5f, -.5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{-1.0f,1.0f}, // vertex uv
            vec3{-.7f,.7f,-.7f}  // vertex normal
        },
        { // 7: vertex
            vec4{.5f, .5f, -.5f, 1}, // position
            vec4{1,1,1,1}, // vertex color
            vec2{0.0f,1.0f}, // vertex uv
            vec3{.7f,.7f,-.7f}  // vertex normal
        },
    };
    GLuint Indicies[] = {
        0, 1, 2,  2, 1, 3,
        0, 4, 1,  1, 4, 5,
        4, 6, 5,  5, 6, 7,
        6, 2, 3,  3, 7, 6,
        0, 2, 6,  6, 4, 0,
        1, 5, 3,  3, 5, 7
    };
    Geometry face = MakeGeometry(verts, 8, Indicies, 36);
    mat4 modelTransform = glm::identity<mat4>();


    // Shaders & Textures
    // TODO: pass filepath for shader and texture
    Shader basicShader = LoadShader("shaders/basic.vert","shaders/basic.frag");
    Texture sampleTex = LoadTexture("textures/wet_koala.jpg");

    // Camera
    vec3 cameraPos = vec3{ 0,0,3 };
    mat4 cameraView = glm::lookAt(
        cameraPos, // camera position
        vec3{ 0,0,0 }, // look at postion
        vec3{ 0,1,0 }); // up vector

    // projection ~flatten to the screen
    mat4 proj = glm::perspective(glm::radians(60.0f), windowWidth /(float)windowHeight, .01f, 10.0f);

    // Uniforms
    SetUniform(basicShader, 0, proj);
    SetUniform(basicShader, 1, cameraView);
    SetUniform(basicShader, 2, modelTransform);
    SetUniform(basicShader, 1, sampleTex, 0);

#pragma endregion


    while (!context.shouldClose()) {
        context.tick();
        context.clear();

        modelTransform = glm::rotate(modelTransform, 0.01f, vec3{ 0,1,0 });
        SetUniform(basicShader, 2, modelTransform);
        DrawGeometry(basicShader, face);
    }

    context.terminate();
    return 0;
}
