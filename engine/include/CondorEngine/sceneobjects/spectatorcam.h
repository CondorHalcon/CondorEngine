#pragma once
#include "CondorEngine/pch.h"
// internal
#include "CondorEngine/sceneobject.h"
#include "CondorEngine/components/camera.h"

namespace CondorEngine
{
	/// @brief Spectator camera SceneObject.
	class DllExport SpectatorCam : public SceneObject
	{
	public:
		/// @brief Class constructor.
		SpectatorCam();
		/// @brief Camera component.
		Camera *camera;
		/// @brief Camera move speed.
		float moveSpeed;
		/// @brief Camera rotation speed.
		float rotationSpeed;
		/// @brief Update spectator camera.
		void Update() override;
	};
}
