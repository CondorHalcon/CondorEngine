#pragma once
#include "../math.h"
#include "../sceneobject.h"
#include "../components/light.h"

namespace CondorEngine {
    /// @brief Scene light object.
    class SceneLight : public SceneObject {
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
        Light* light;
    };
}