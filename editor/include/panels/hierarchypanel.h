#pragma once
#include "editorpanel.h"
#include <CondorEngine.hpp>

using namespace CondorEngine;

namespace CondorEditor
{
    class HierarchyPanel : public EditorPanel
    {
    private:
        static inline HierarchyPanel* instance = nullptr;
    public:
        static HierarchyPanel* Instance() {
            if (instance == nullptr) {
                instance = new HierarchyPanel();
            }
            return instance;
        }
        
        virtual const char* getTitle() { return "Hierarchy"; }

        virtual void OnGui() override;
    private:
        static void DrawObjectHierarchy(SceneObject*& object);
    };
}