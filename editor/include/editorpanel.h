#pragma once

namespace CondorEditor
{
    class EditorPanel
    {
    public:
        virtual const char* getTitle() = 0;
        virtual void OnGui() = 0;
    };
}