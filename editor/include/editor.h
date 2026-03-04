#pragma once
#include <CondorEngine.hpp>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <vector>
using namespace CondorEngine;

namespace CondorEditor
{
    class EditorPanel;

    class Editor
    {
    private:
        Editor();
        ~Editor();
        static Editor* instance;
        
    public:
        static Editor* Instance();

        void init();
        void terminate();

        std::vector<EditorPanel*> panels;
        Camera* sceneCamera;
        Object* selectedSceneObject;

        bool playMode;
    };
}