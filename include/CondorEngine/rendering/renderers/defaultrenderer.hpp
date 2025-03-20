#pragma once
#include "CondorEngine/pch.h"
#include "CondorEngine/rendering/renderer.h"
#include "CondorEngine/rendering/renderfeatures/colorrenderfeature.hpp"

namespace CondorEngine
{
    namespace Rendering
    {
        class DllExport DefaultRenderer : public Renderer
        {
        public:
            DefaultRenderer() {
                featuresMain = std::vector<RenderFeature*>{ new ColorRenderFeature() };
            }
        };
    }
}