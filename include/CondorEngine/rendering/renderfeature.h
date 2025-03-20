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

            virtual void Render();
        };
    }
}