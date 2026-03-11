#pragma once
#include "CondorEngine/pch.h"
#include "CondorEngine/material.h"
#include "CondorEngine/resourcemanager.h"

namespace CondorEngine
{
    /// @brief Texture UV material.
    class UV : public Material
    {
        REFLECT_CLASS(CondorEngine::UV, Material)
    public:
        UV() : Material("UV", ResourceManager::LoadShader("CondorEngine/shaders/directional.vert", "CondorEngine/shaders/uv.frag")) {}
    };
}