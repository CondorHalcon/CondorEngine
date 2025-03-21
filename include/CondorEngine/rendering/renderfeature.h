#pragma once
#include "CondorEngine/pch.h"

namespace CondorEngine
{
    namespace Rendering
    {
        class DllExport RenderFeature
        {
        public:
            RenderFeature();

            /// @brief Pre proccess render step.
            /// @note By default this is called before clearing the color, depth, and stencil buffers.
            virtual void PreProccess();
            /// @brief Main render step
            virtual void Render();
            /// @brief post process render step
            virtual void PostProcess();
        };
    }
}