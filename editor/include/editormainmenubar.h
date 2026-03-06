#pragma once

namespace CondorEditor
{
    class EditorMainMenuBar
    {
    private:
        /// @brief 
        EditorMainMenuBar();
        ~EditorMainMenuBar();
        static inline EditorMainMenuBar* instance = nullptr;
    public:
        static EditorMainMenuBar* Instance();

        void DrawMainMenuBar();

    private:
        void ProjectMenu();
        void EditMenu();
        void PanelsMenu();
        void PluginsMenu();
    private:
        void NewSceneObjectSubMenu();
    };
}
