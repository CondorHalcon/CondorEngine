#pragma once
// internal
#include "../sceneobject.h"
#include "../components/camera.h"

namespace CondorEngine {
	/// @brief Spectator camera SceneObject.
	class SpectatorCam : public SceneObject
	{
	public:
		/// @brief Class constructor.
		SpectatorCam();
		/// @brief Camera component.
		Camera* camera;
		/// @brief Camera move speed.
		float moveSpeed;
		/// @brief Camera rotation speed.
		float rotationSpeed;
		/// @brief Update spectator camera.
		void Update() override;
	};
}

