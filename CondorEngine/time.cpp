#include "time.h"
// third party
#include "glfw/glfw3.h"

double CondorEngine::Time::lastFrameTime = 0.0;
double CondorEngine::Time::accumulatedFixedTime = 0.0;
float CondorEngine::Time::fixedTimeStep = 0.02f;

void CondorEngine::Time::timeInit()
{
    fixedTimeStep = 0.0166f;
    lastFrameTime = glfwGetTime();
    accumulatedFixedTime = 0;
}

void CondorEngine::Time::timeUpdate()
{
    lastFrameTime = glfwGetTime();
}

float CondorEngine::Time::time() {
    return glfwGetTime();
}

float CondorEngine::Time::deltaTime() 
{
    double currentTime = glfwGetTime();
    float deltaTime = (currentTime - lastFrameTime);
    return deltaTime;
}

float CondorEngine::Time::fixedDeltaTime() 
{
    return (float)accumulatedFixedTime;
}
