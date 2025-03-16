#include "CondorEngine.hpp"

int RunApplication(Application* app, const char* title, CondorEngine::Vector2 resolution) {
    try {
        if (!app->init(resolution.x, resolution.y, title)) {
            throw std::exception("Failed to initialise application.");
        }
        CondorEngine::Time::fixedTimeStep = .02f;

        CondorEngine::Debug::LogGLEnvironment();

        app->runtime();
    }
    catch (const std::exception& e) {
        CondorEngine::Debug::LogError(e.what());
        return EXIT_FAILURE;
    }

    if (app) {
        app->terminate();
    }
    return EXIT_SUCCESS;
}