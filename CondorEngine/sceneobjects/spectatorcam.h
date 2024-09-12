#pragma once
#include "../core.h"
#include "../components/camera.h"

namespace CondorEngine {
	class SpectatorCam : public SceneObject
	{
	public:
		SpectatorCam();
		Camera* camera;
		void Update() override;
	};
}

