#pragma once
#include "CondorEngine/pch.h"
#include "CondorEngine.hpp"
// std
#include <string>
#include <vector>

namespace CondorEngine
{
    class DllExport Factory
    {
    public:
        static Component* Create(const std::string& type) {
            if (type == "CondorEngine::Camera") return new Camera();
            if (type == "CondorEngine::Mesh") return new Mesh(MeshData());
            if (type == "CondorEngine::Light") return new Light();
            return nullptr;
        }
    };
}
