#pragma once
#include "CondorEngine/pch.h"
#include "CondorEngine/material.h"
#include "CondorEngine/resourcemanager.h"

namespace CondorEngine
{
    /// @brief Texture UV material.
    class UV : public Material
    {
    public:
        UV() : Material(ResourceManager::LoadShader("shaders/directional.vert", "shaders/uv.frag")) {}
    };
}