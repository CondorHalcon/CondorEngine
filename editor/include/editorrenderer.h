#pragma once
#include <CondorEngine.hpp>
#include <CondorEngine/rendering/renderfeatures/imguirenderfeature.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include "editor.h"
#include "editorpanel.h"
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

    class SceneViewRenderFeature : public RenderFeature
    {
    private:
        SceneViewRenderFeature();
        ~SceneViewRenderFeature();
        static SceneViewRenderFeature* instance;
    public:
        static SceneViewRenderFeature* Instance();

        GLuint sceneFBO = 0;
        GLuint sceneColorTex = 0;
        GLuint sceneDepthRBO = 0;
        Vector2Int sceneSize = { 1280, 720 };

        void CreateSceneFramebuffer(int width, int height);

        void SetBuffer();

        virtual void Render() override;
    };

    class EditorRenderer : public Renderer
    {
    public:
        /// @brief Class constructor.
        EditorRenderer();

        virtual void init() override;
    };
}