#pragma once
#include "../core.h"
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
		float moveSpeed;
		float rotationSpeed;
		/// @brief Update spectator camera.
		void Update() override;
	};
}

