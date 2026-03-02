#pragma once
#include "CondorEngine/pch.h"
// internal
#include "CondorEngine/serialization.hpp"
#include "CondorEngine/sceneobject.h"
#include "CondorEngine/components/camera.h"

namespace CondorEngine
{
	/// @brief Spectator camera SceneObject.
	class DllExport SpectatorCam : public SceneObject
	{
		REFLECT_CLASS(SpectatorCam, SceneObject)
	public:
		/// @brief Class constructor.
		SpectatorCam();
		/// @brief Camera component.
		FIELD(Camera*, camera, SpectatorCam);
		/// @brief Camera move speed.
		FIELD(float, moveSpeed, SpectatorCam)
		/// @brief Camera rotation speed.
		FIELD(float, rotationSpeed, SpectatorCam)
		/// @brief Update spectator camera.
		void Update() override;
	};
}
