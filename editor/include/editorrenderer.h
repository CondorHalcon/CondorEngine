#pragma once
#include <CondorEngine.hpp>
#include <CondorEngine/Rendering.hpp>
#include <CondorEngine/rendering/renderfeatures/imguirenderfeature.h>

using namespace CondorEngine;
using namespace CondorEngine::Rendering;

namespace CondorEditor
{
    class EditorRenderFeature : public ImGuiRenderFeature
    {
    public:
        EditorRenderFeature();

        const char* rootDockspace = "RootDockspace";

        virtual void Render() override;

        void BuildDefaultDockLayout(ImGuiID dockspaceId, ImGuiViewport* viewport);
        void MainMenuBar();
    };

    class EditorRenderer : public Renderer
    {
    public:
        /// @brief Class constructor.
        EditorRenderer();

        virtual void init() override;
    };
}