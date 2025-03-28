#pragma once
#include "CondorEngine/pch.h"
#include "CondorEngine/material.h"
#include "CondorEngine/resourcemanager.h"

namespace CondorEngine
{
    /// @brief Texture UV material.
    class Depth : public Material
    {
    public:
        Depth() : Material(ResourceManager::LoadShader("shaders/directional.vert", "shaders/depth.frag")) {}
    };
}
