#pragma once
#include "CondorEngine/pch.h"
#include "CondorEngine/rendering/renderer.h"
#include "CondorEngine/rendering/renderfeatures/colorrenderfeature.hpp"

namespace CondorEngine
{
    namespace Rendering
    {
        /// @brief Engine default renderer.
        class DllExport DefaultRenderer : public Renderer
        {
        public:
            /// @brief Class constructor.
            DefaultRenderer() {}

            virtual void init() override {
                Renderer::init();

                // initialize render features
                featuresMain = std::vector<RenderFeature*>{ new ColorRenderFeature() };
            }
        };
    }
}
