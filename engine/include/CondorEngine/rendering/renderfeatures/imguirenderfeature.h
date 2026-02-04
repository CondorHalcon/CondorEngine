#pragma once
#include "CondorEngine/pch.h"
#include "CondorEngine/rendering/renderfeature.h"
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace CondorEngine
{
    namespace Rendering
    {
        class DllExport ImGuiRenderFeature : public RenderFeature
        {
        public:
            ImGuiRenderFeature();

            const char* rootDockspace = "RootDockspace";

            virtual void Render() override;

            void RootDockspace();

            virtual void PostProcess() override;
        };
    }
}
