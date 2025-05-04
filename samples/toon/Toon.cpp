#include <CondorEngine.hpp>
#include <CondorEngine/sceneobjects/spectatorcam.h>
#include <stdexcept>
#include "toonmat.hpp"
#include "toonsceneobjects.hpp"
#include "toonrenderer.hpp"

using namespace CondorEngine;

class ToonScene : public Scene
{
public:
    ToonScene() {
        // directional light
        light = DirectionalLight(ColorRGB{ .7, .7, .7 }, Vector3{ 0, -.3, -.7 });

        // camera
        SpectatorCam* camera = this->Instantiate<SpectatorCam>(new SpectatorCam(), Vector3{ 0, 1, 10 });
        camera->Rotate(Vector3{ 0, 180, 0 });

        // level
        Ground* ground = this->Instantiate<Ground>(new Ground(), Vector3{ 0, 0, 0 });
    }
};

int main() {
    Application* app = Application::Instance();

    try {
        app->renderer = new ToonRenderer();
        app->init(1280, 720, "Toon Sample");
        app->activeScene = new ToonScene();
        app->runtime();
        app->terminate();
    }
    catch (const std::exception& e) {
        Debug::LogError(e.what());
        return 1;
    }
    return 0;
}
