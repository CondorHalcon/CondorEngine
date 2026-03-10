#pragma once
#include "CondorEngine/pch.h"
#include "CondorEngine/serialization.hpp"

namespace CondorEngine
{
    struct DllExport LayerMask
    {
        REFLECT_STRUCT(CondorEngine::LayerMask)
            REFLECT_FIELD(unsigned int, value)
            LayerMask(unsigned int value = 0x1);
        std::vector<std::string> getLayers();
        std::string getLabel();

        struct AutoRegister_LayerMask_Draw
        {
            AutoRegister_LayerMask_Draw();
        };
        static inline AutoRegister_LayerMask_Draw _AutoRegister_LayerMask_Draw;
    };
}