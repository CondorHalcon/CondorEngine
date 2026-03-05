#pragma once
#include <CondorEngine.hpp>
#include <vector>

using namespace CondorEngine;

namespace CondorEditor
{
    class EditorPanel;
    class EditorRenderFeature;

    class Editor
    {
        friend EditorRenderFeature; // needs to access private member `panels`
    private:
        Editor();
        ~Editor();
        static Editor* instance;
        
    public:
        static Editor* Instance();

        void init();
        void terminate();

        Camera* sceneCamera;
        Object* selectedSceneObject;

        bool playMode;

    private:
        std::vector<EditorPanel*> panels;

    public:
        void AddPanel(EditorPanel* panel);
        bool RemovePanel(EditorPanel* panel, bool destroy = true);
    };
}