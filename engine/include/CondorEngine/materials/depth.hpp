#pragma once
#include "CondorEngine/pch.h"
#include "CondorEngine/material.h"
#include "CondorEngine/resourcemanager.h"

namespace CondorEngine
{
    /// @brief Texture UV material.
    class Depth : public Material
    {
        REFLECT_CLASS(CondorEngine::Depth, Material)
    public:
        Depth() : Material("Depth", ResourceManager::LoadShader("CondorEngine/shaders/directional.vert", "CondorEngine/shaders/depth.frag")) {}
    };
}
