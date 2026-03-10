#pragma once
#include "CondorEngine/pch.h"
#include "CondorEngine/rendering/renderer.h"
#include "CondorEngine/rendering/renderfeatures/colorrenderfeature.hpp"
#include "CondorEngine/rendering/renderfeatures/directionalshadowmappingrenderfeature.hpp"

namespace CondorEngine
{
    namespace Rendering
    {
        /// @brief Engine default renderer.
        class DllExport DefaultRenderer : public Renderer
        {
            REFLECT_CLASS(CondorEngine::Rendering::DefaultRenderer, Renderer)
        public:
            /// @brief Class constructor.
            DefaultRenderer() {}

            virtual void init() override {
                Renderer::init();

                // initialize render features
                features = std::vector<RenderFeature*>{ new ColorRenderFeature(), DirectionalShadowMappingRenderFeature::Instance() };
            }

            virtual void Render() override {
                if (Camera::Main() == nullptr) { // no camera to render with
                    ResetScreen();
                    return;
                }

                Renderer::Render();
            }
        };
    }
}
