#pragma once
#include "application.h"

namespace CondorEngine 
{
    static double lastFrameTime = 0.0;
    static double accumulatedFixedTime = 0.0;
    void timeInit();
    void timeUpdate();
    static float fixedTimeStep = 0.02f;
    float time();
    float deltaTime();
}
