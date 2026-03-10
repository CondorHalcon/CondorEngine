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
		REFLECT_CLASS(CondorEngine::SpectatorCam, SceneObject)
	public:
		/// @brief Default class constructor.
		SpectatorCam();
		/// @brief Class Constructor.
		SpectatorCam(std::string name);
		/// @brief Camera component.
		REFLECT_FIELD(Camera*, camera)
		/// @brief Camera move speed.
		REFLECT_FIELD(float, moveSpeed)
		/// @brief Camera rotation speed.
		REFLECT_FIELD(float, rotationSpeed)
		/// @brief Update spectator camera.
		void Update() override;
	};
}
