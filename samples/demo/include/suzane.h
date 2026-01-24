#pragma once
#include <CondorEngine.hpp>

using namespace CondorEngine;

class Suzane : public SceneObject
{
public:
    /// @brief 
    /// @param material 
    Suzane(Material* material);
    /// @brief 
    Suzane();

    Mesh* mesh;
};
