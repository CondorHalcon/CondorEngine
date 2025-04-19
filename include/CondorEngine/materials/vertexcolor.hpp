#pragma once
#include "CondorEngine/pch.h"
#include "CondorEngine/material.h"
#include "CondorEngine/resourcemanager.h"

namespace CondorEngine
{
    /// @brief Mesh vertex color material.
    class VertexColor : public Material
    {
    public:
        /// @brief Class constructor
        VertexColor() : Material(ResourceManager::LoadShader("CondorEngine/shaders/basic.vert", "CondorEngine/shaders/vertexcolor.frag")) {
            this->name = "CondorEngine::VertexColor";
        }
    };
}