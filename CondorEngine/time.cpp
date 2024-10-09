#include "time.h"
#include "glfw/glfw3.h"
#include "debug.h"

#include <string>

void CondorEngine::timeInit()
{
    Debug::Log("init fixedTimeStep" + std::to_string(fixedTimeStep));
    fixedTimeStep = 0.0166f;
    Debug::Log("init fixedTimeStep" + std::to_string(fixedTimeStep));
    lastFrameTime = glfwGetTime();
    accumulatedFixedTime = 0;
}

void CondorEngine::timeUpdate()
{
    lastFrameTime = glfwGetTime();
}

float CondorEngine::time() {
    return glfwGetTime();
}

float CondorEngine::deltaTime() 
{
    double currentTime = glfwGetTime();
    float deltaTime = (currentTime - lastFrameTime);
    return deltaTime;
}
