#pragma once
#include "application.h"

namespace CondorEngine 
{
    static double lastFrameTime;
    static double accumulatedFixedTime;
    static void timeInit();
    static void timeUpdate();
    static float fixedTimeStep;
    static float time();
    static float deltaTime();
}
