#pragma once
#include "CondorEngine/pch.h"
#include "CondorEngine/material.h"
#include "CondorEngine/resourcemanager.h"

namespace CondorEngine
{
    /// @brief Mesh vertex color material.
    class VertexColor : public Material
    {
        REFLECT_CLASS(CondorEngine::VertexColor, Material)
    public:
        /// @brief Class constructor
        VertexColor() : Material("Vertex Color", ResourceManager::LoadShader("CondorEngine/shaders/basic.vert", "CondorEngine/shaders/vertexcolor.frag")) {}
    };
}