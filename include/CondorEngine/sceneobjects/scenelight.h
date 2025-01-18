#pragma once
#include "CondorEngine/pch.h"
// internal
#include "CondorEngine/math.hpp"
#include "CondorEngine/sceneobject.h"
#include "CondorEngine/components/light.h"

namespace CondorEngine
{
    /// @brief Scene light object.
    class DllExport SceneLight : public SceneObject
    {
    public:
        /// @brief Class constructor
        SceneLight();
        /// @brief Class constructor
        /// @param lightColor Color of the light.
        SceneLight(ColorRGB lightColor);
        /// @brief Class constructor
        /// @param lightColor Color of the light.
        /// @param lightDirection Direction of the light.
        SceneLight(ColorRGB lightColor, Vector3 lightDirection);

    public:
        /// @brief Light component.
        Light *light;
    };
}