#pragma once

namespace CondorEngine 
{
    class Time
    {
    public:
        static double lastFrameTime;
        static double accumulatedFixedTime;
        static void timeInit();
        static void timeUpdate();
        static float fixedTimeStep;
        static float time();
        static float deltaTime();
        static float fixedDeltaTime();
    };
}
