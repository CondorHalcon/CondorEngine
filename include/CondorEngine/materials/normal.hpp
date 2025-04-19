#pragma once
#include "CondorEngine/pch.h"
#include "CondorEngine/material.h"
#include "CondorEngine/resourcemanager.h"

namespace CondorEngine
{
    /// @brief Object normal material.
    class Normal : public Material
    {
    public:
        /// @brief Class constructor.
        Normal() : Material(ResourceManager::LoadShader("CondorEngine/shaders/directional.vert", "CondorEngine/shaders/normal.frag")) {
            this->name = "CondorEngine::Normal";
        }
    };
}