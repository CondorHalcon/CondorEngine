#pragma once
#include "CondorEngine/pch.h"
// internal
#include "CondorEngine/math.hpp"
#include "CondorEngine/renderer.h"
#include "CondorEngine/component.h"

namespace CondorEngine
{
	/// @brief Type of light component.
	enum DllExport LightType
	{
		Point,
		Spot
	};

	/// @brief Light component class.
	class DllExport Light : public Component
	{
	public:
		/// @brief Class constructor.
		Light();
		/// @brief Class deconstructor.
		~Light();
		// TODO add accessors and make private
	public:
		/// @brief Light Color.
		ColorRGB color;
		/// @brief Light direction.
		Vector3 direction;
		/// @brief Light type.
		LightType type;

	public:
		/// @brief Get light color.
		/// @return Light `ColorRGB` color.
		ColorRGB getLightColor();
		/// @brief Get light direction.
		/// @return Light direction.
		Vector3 getLightDirection();
		/// @brief Get light world position.
		/// @return World position.
		Vector3 getLightPosition();
	};
}
