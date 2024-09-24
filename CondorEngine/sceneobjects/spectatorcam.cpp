#include "spectatorcam.h"
#include "../application.h"
#include "../debug.h"

CondorEngine::SpectatorCam::SpectatorCam()
{
	this->name = "CondorEngine::SpectatorCam";
	this->camera = AddComponent<Camera>(new Camera());
}

void CondorEngine::SpectatorCam::Update()
{
    // move forward back
    if (Application::Input(GLFW_KEY_W)) {
        Move(getForward() * .01f);
    }
    if (Application::Input(GLFW_KEY_S)) {
        Move(getForward() * -.01f);
    }
    // move right left
    if (Application::Input(GLFW_KEY_D)) {
        Move(getRight() * -.01f);
    }
    if (Application::Input(GLFW_KEY_A)) {
        Move(getRight() * .01f);
    }
    // move up down
    if (Application::Input(GLFW_KEY_E)) {
        Move(getUp() * .01f);
    }
    if (Application::Input(GLFW_KEY_Q)) {
        Move(getUp() * -.01f);
    }
    // rotate up down
    if (Application::Input(GLFW_KEY_UP)) {
        Rotate(CondorEngine::Vector3{ -.1, 0, 0 });
    }
    if (Application::Input(GLFW_KEY_DOWN)) {
        Rotate(CondorEngine::Vector3{ .1, 0, 0 });
    }
    // rotate left right
    if (Application::Input(GLFW_KEY_RIGHT)) {
        Rotate(CondorEngine::Vector3{ 0, -.1, 0 });
    }
    if (Application::Input(GLFW_KEY_LEFT)) {
        Rotate(CondorEngine::Vector3{ 0, .1, 0 });
    }
}
