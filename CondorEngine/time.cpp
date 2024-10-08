#include "time.h"
#include "glfw/glfw3.h"

void CondorEngine::timeInit()
{
	fixedTimeStep = 0.0166f;
    lastFrameTime = glfwGetTime();
}

void CondorEngine::timeUpdate()
{
    lastFrameTime = glfwGetTime();
}

float CondorEngine::time() {
    return glfwGetTime() / 1000.0f;
}

float CondorEngine::deltaTime() 
{
    double currentTime = glfwGetTime();
    float deltaTime = (currentTime - lastFrameTime) / 1000.0f;
    return deltaTime;
}