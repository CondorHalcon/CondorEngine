#include <CondorEngine.hpp>
#include <CondorEngine/scenes/defaultscene.h>
#include "editor.h"
#include "editorrenderer.h"
using namespace CondorEngine;
using namespace CondorEditor;

int main() {
    Application* engine = Application::Instance();
    Editor* editor = Editor::Instance();
    EditorRenderer* renderer = new EditorRenderer();
    try {
        // renderer
        engine->renderer = renderer;

        // initialize engine
        if (!engine->init(1280, 720, "CondorEditor")) {
            throw std::runtime_error("CondorEditor :: Failed to initialise application.");
        }

        // initialize editor
        editor->init();

        engine->activeScene = new DefaultScene();

        engine->runtime();
    }
    catch (const std::exception& e) {
        Debug::LogError(e.what());
        return EXIT_FAILURE;
    }

    engine->terminate();
    return EXIT_SUCCESS;
}