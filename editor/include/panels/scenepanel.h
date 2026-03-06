#pragma once
#include "editorpanel.h"
#include <CondorEngine.hpp>

using namespace CondorEngine;

namespace CondorEditor
{
    class ScenePanel : public EditorPanel
    {
    private:
        static inline ScenePanel* instance = nullptr;
    public:
        static ScenePanel* Instance() {
            if (instance == nullptr) {
                instance = new ScenePanel();
            }
            return instance;
        }

        virtual const char* getTitle() { return "Scene"; }

        virtual void OnGui() override;
    };
}