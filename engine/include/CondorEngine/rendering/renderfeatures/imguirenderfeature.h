#pragma once
#include "CondorEngine/pch.h"
#include "CondorEngine/rendering/renderfeature.h"

namespace CondorEngine
{
    namespace Rendering
    {
        class DllExport ImGuiRenderFeature : public RenderFeature
        {
        public:
            ImGuiRenderFeature();

            virtual void Render() override;

            virtual void PostProcess() override;
        };
    }
}
