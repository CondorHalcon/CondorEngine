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
        UV() : Material(ResourceManager::LoadShader("CondorEngine/shaders/directional.vert", "CondorEngine/shaders/uv.frag")) {
            this->name = "CondorEngine::UV";
        }
    };
}