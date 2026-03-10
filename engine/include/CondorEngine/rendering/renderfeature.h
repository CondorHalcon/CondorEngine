#pragma once
#include "CondorEngine/pch.h"
#include "CondorEngine/object.h"

namespace CondorEngine
{
    namespace Rendering
    {
        class DllExport RenderFeature : public Object
        {
            REFLECT_CLASS(CondorEngine::Rendering::RenderFeature, Object)
        public:
            RenderFeature();

            /// @brief Pre proccess render step.
            /// @note By default this is called before clearing the color, depth, and stencil buffers. It is therefore advised to only write to custom framebuffers and not the main screen framebuffer.
            virtual void PreProccess();
            /// @brief Main render step
            virtual void Render();
            /// @brief post process render step
            virtual void PostProcess();
        };
    }
}