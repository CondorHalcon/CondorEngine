#pragma once
#include "CondorEngine/pch.h"
#include "CondorEngine/material.h"
#include "CondorEngine/resourcemanager.h"

namespace CondorEngine
{
    /// @brief Object normal material.
    class Normal : public Material
    {
        REFLECT_CLASS(CondorEngine::Normal, Material)
    public:
        /// @brief Class constructor.
        Normal() : Material("Normal", ResourceManager::LoadShader("CondorEngine/shaders/directional.vert", "CondorEngine/shaders/normal.frag")) {}
    };
}