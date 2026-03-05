#pragma once
#include "editorpanel.h"
#include "editor.h"

using namespace CondorEngine;

namespace CondorEditor
{
    class ProjectPanel : public EditorPanel
    {
    private:
        static inline ProjectPanel* instance = nullptr;
    public:
        static ProjectPanel* Instance() {
            if (instance == nullptr) {
                instance = new ProjectPanel();
            }
            return instance;
        }

        virtual const char* getTitle() { return "Project"; }

        virtual void OnGui() override;
    };
}