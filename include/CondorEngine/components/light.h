#pragma once
#include "CondorEngine/pch.h"
// internal
#include "CondorEngine/math.hpp"
#include "CondorEngine/renderer.h"
#include "CondorEngine/component.h"

namespace CondorEngine
{
	/// @brief Light component class.
	class DllExport Light : public Component
	{
	public:
		/// @brief Class constructor.
		/// @param col Color of the light.
		/// @param dir Direction of the light.
		/// @param cutoff Cutoff angle of the light (used to make spotlights).
		Light(ColorRGB col = ColorRGB{ 1,1,1 }, Vector3 dir = Vector3{ 0, -1, 0 }, float cutoff = 180);
		// TODO add accessors and make private
	public:
		/// @brief Light Color.
		ColorRGB color;
		/// @brief Light direction.
		Vector3 direction;
		float range;
		float intensity;
		/// @brief 
		float cutoff;
		/// @brief 
		float outerCutoff;

	public:
		virtual void LateUpdate() override;
		/// @brief Get light color.
		/// @return Light `ColorRGB` color.
		ColorRGB getLightColor();
		/// @brief Get light direction.
		/// @return Light direction.
		Vector3 getLightDirection();
		/// @brief Get light world position.
		/// @return World position.
		Vector3 getLightPosition();
		float getLightCutoff();
		float getLightOuterCutoff();
	};
}
