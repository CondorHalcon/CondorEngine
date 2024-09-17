#include "spectatorcam.h"
#include "../application.h"

CondorEngine::SpectatorCam::SpectatorCam()
{
	this->name = "CondorEngine::SpectatorCam";
	this->camera = AddComponent<Camera>(new Camera());
}

void CondorEngine::SpectatorCam::Update()
{
    // move forwad back
    if (Application::Input(GLFW_KEY_W)) {
        Move(CondorEngine::Vector3{ 0, 0, -.01 });
    }
    if (Application::Input(GLFW_KEY_S)) {
        Move(CondorEngine::Vector3{ 0, 0, .01 });
    }
    // move right left
    if (Application::Input(GLFW_KEY_A)) {
        Move(CondorEngine::Vector3{ -.01, 0, 0 });
    }
    if (Application::Input(GLFW_KEY_D)) {
        Move(CondorEngine::Vector3{ .01, 0, 0 });
    }
    // move up down
    if (Application::Input(GLFW_KEY_Q)) {
        Move(CondorEngine::Vector3{ 0, -.01, 0 });
    }
    if (Application::Input(GLFW_KEY_E)) {
        Move(CondorEngine::Vector3{ 0, .01, 0 });
    }
    // rotate up down
    if (Application::Input(GLFW_KEY_UP)) {
        Rotate(CondorEngine::Vector3{ .1, 0, 0 });
    }
    if (Application::Input(GLFW_KEY_DOWN)) {
        Rotate(CondorEngine::Vector3{ -.1, 0, 0 });
    }
    // rotate left right
    if (Application::Input(GLFW_KEY_RIGHT)) {
        Rotate(CondorEngine::Vector3{ 0, -.1, 0 });
    }
    if (Application::Input(GLFW_KEY_LEFT)) {
        Rotate(CondorEngine::Vector3{ 0, .1, 0 });
    }
}
