#pragma once
#include "../math.h"
#include "../core.h"
// third party
#include "glm/ext.hpp"
#include "glfw/glfw3.h"

namespace CondorEngine {
	/// @brief Camera component class.
	class Camera : public Component
	{
	public:
		/// @brief Class constructor.
		Camera();
		/// @brief Class deconstructor.
		~Camera();
	private:
		/// @brief Main render camera.
		static Camera* main;
	public:
		/// @brief Camera FOV.
		float fov = 60.0f;
		/// @brief Camera near clipping plane.
		float nearClippingPlane = .01f;
		/// @brief Camera far clipping plane.
		float farClippingPlane = 10.0f;
	public:
		/// @brief Get the main camera.
		/// @return The current main render camera.
		static Camera* Main();
		/// @brief Set the main Camera. `WARNING`: This method does not delete the current main camera from memory.
		/// @param camera
		static void SetMainCamera(Camera* camera);
	public:
		/// @brief Get this Camera's world position.
		/// @return World position.
		Vector3 getPosition();
		/// @brief Get this Camera's view matrix.
		/// @return View matrix.
		Transform getViewMatrix();
		/// @brief Get this Camera's projection matrix.
		/// @return Projection matrix.
		Transform getProjectionMatrix();
	};
}

