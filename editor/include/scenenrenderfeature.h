#pragma once
#include <CondorEngine.hpp>
#include <CondorEngine/Rendering.hpp>

using namespace CondorEngine;
using namespace CondorEngine::Rendering;

namespace CondorEditor
{
    class SceneViewRenderFeature : public RenderFeature
    {
    private:
        SceneViewRenderFeature();
        ~SceneViewRenderFeature();
        static inline SceneViewRenderFeature* instance = nullptr;
    public:
        static SceneViewRenderFeature* Instance() {
            if (instance == nullptr) {
                instance = new SceneViewRenderFeature();
            }
            return instance;
        }

        GLuint sceneFBO = 0;
        GLuint sceneColorTex = 0;
        GLuint sceneDepthRBO = 0;
        Vector2Int sceneSize = { 1280, 720 };

        void CreateSceneFramebuffer(int width, int height);

        void SetBuffer();

        virtual void Render() override;
    };
}
