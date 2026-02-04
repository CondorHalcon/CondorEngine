#pragma once
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <CondorEngine.hpp>
using namespace CondorEngine;

namespace CondorEditor
{
    class EditorPanel
    {
    public:
        virtual void OnGui() = 0;
    };
}