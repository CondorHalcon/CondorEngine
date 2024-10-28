#pragma once

namespace CondorEngine 
{
    /// @brief Engine time class.
    class Time
    {
    public:
        /// @brief Time at last application frame.
        static double lastFrameTime;
        /// @brief Accumulated time since last physics frame.
        static double accumulatedFixedTime;
        /// @brief Initialise the time class.
        static void timeInit();
        /// @brief Update frame time.
        static void timeUpdate();
        /// @brief Fixed physics time step.
        static float fixedTimeStep;
        /// @brief Get the current time.
        static float time();
        /// @brief Get this frame's delta time.
        /// @return Delta time in seconds.
        static float deltaTime();
        /// @brief Get the fixed delta time.
        /// @return Fixed delta time in seconds.
        static float fixedDeltaTime();
    };
}
