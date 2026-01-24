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
        /// @param lightColor Color of the light.
        /// @param lightDirection Direction of the light.
        /// @param cutoff Angle to cutoff the light (used to make spotlights).
        SceneLight(ColorRGB lightColor = ColorRGB{ 1, 1, 1 }, Vector3 lightDirection = Vector3{ 0, -1, 0 }, float cutoff = 360);

    public:
        /// @brief Light component.
        Light *light;
    };
}