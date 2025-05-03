#include <CondorEngine.hpp>
#include <CondorEngine/scenes/defaultscene.h>
#include <stdexcept>

using namespace CondorEngine;

class ToonMat : public Material
{
public:
    ToonMat() : Material(ResourceManager::LoadShader("shaders/directional.vert", "shaders/phong.frag")) {}
};

class ToonSuzane : public SceneObject
{
public:
    ToonSuzane() {
        //delete mesh->material;
        //mesh->material = new ToonMat();
    }
};

class ToonScene : public DefaultScene
{
public:
    ToonScene() {
        ToonSuzane* suzan = Instantiate<ToonSuzane>(new ToonSuzane());

    }
};

int main() {
    Application* app = Application::Instance();

    try {
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
