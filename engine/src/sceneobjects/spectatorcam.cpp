#include "CondorEngine/sceneobjects/spectatorcam.h"
// internal
#include "CondorEngine/time.hpp"
#include "CondorEngine/application.h"
#include "CondorEngine/debug.hpp"

CondorEngine::SpectatorCam::SpectatorCam()
{
    this->name = "CondorEngine::SpectatorCam";
    this->camera = AddComponent<Camera>(new Camera());
    this->moveSpeed = 5;
    this->rotationSpeed = 50;
}

void CondorEngine::SpectatorCam::Update()
{
    // move forward back
    if (Application::Input(GLFW_KEY_W))
    {
        Move(getForward() * moveSpeed * Time::deltaTime());
    }
    if (Application::Input(GLFW_KEY_S))
    {
        Move(getForward() * -moveSpeed * Time::deltaTime());
    }
    // move right left
    if (Application::Input(GLFW_KEY_D))
    {
        Move(getRight() * -moveSpeed * Time::deltaTime());
    }
    if (Application::Input(GLFW_KEY_A))
    {
        Move(getRight() * moveSpeed * Time::deltaTime());
    }
    // move up down
    if (Application::Input(GLFW_KEY_E))
    {
        Move(getUp() * moveSpeed * Time::deltaTime());
    }
    if (Application::Input(GLFW_KEY_Q))
    {
        Move(getUp() * -moveSpeed * Time::deltaTime());
    }
    // rotate up down
    if (Application::Input(GLFW_KEY_UP))
    {
        Rotate(CondorEngine::Vector3{-1, 0, 0} * rotationSpeed * Time::deltaTime());
    }
    if (Application::Input(GLFW_KEY_DOWN))
    {
        Rotate(CondorEngine::Vector3{1, 0, 0} * rotationSpeed * Time::deltaTime());
    }
    // rotate left right
    if (Application::Input(GLFW_KEY_RIGHT))
    {
        Rotate(CondorEngine::Vector3{0, -1, 0} * rotationSpeed * Time::deltaTime());
    }
    if (Application::Input(GLFW_KEY_LEFT))
    {
        Rotate(CondorEngine::Vector3{0, 1, 0} * rotationSpeed * Time::deltaTime());
    }
}
