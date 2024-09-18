#pragma once
#include "../math.h"
#include "../renderer.h"
#include "../core.h"

namespace CondorEngine {
	enum LightType
	{
		Point,
		Spot
	};

	class Light : public Component
	{
	public:
		Light();
	private:
		ColorRGB color;
		Vector3 direction;
		LightType type;

	public:
		ColorRGB getLightColor();
		Vector3 getLightDirection();
		Vector3 getLightPosition();
	};
}

