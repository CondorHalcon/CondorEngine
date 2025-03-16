#include <CondorEngine.hpp>
#include <CondorEngine/scenes/defaultscene.h>
#include <stdexcept>

using namespace CondorEngine;

class ToonMat : public Material {};

class ToonScene : public DefaultScene
{
public:
};

int main() {
    Application* app = Application::Instance();
    app->activeScene = new DefaultScene();
    return RunApplication(app, "Toon Sample", Vector2{ 1280, 720 });
}
