#pragma once
#include "editorpanel.h"
#include <CondorEngine.hpp>

using namespace CondorEngine;

namespace CondorEditor
{
    class ConsolePanel : public EditorPanel
    {
    private:
        static inline ConsolePanel* instance = nullptr;
    public:
        static ConsolePanel* Instance() {
            if (instance == nullptr) {
                instance = new ConsolePanel();
            }
            return instance;
        }
        
        virtual const char* getTitle() { return "Console"; }

        virtual void OnGui() override;
    };
}