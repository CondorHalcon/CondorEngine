#pragma once
#include "CondorEngine/pch.h"
#include "CondorEngine/serialization.hpp"
// internal
#include "CondorEngine/math.hpp"
#include "CondorEngine/component.h"

namespace CondorEngine
{
	/// @brief Camera component class.
	class DllExport Camera : public Component
	{
		REFLECT_CLASS(CondorEngine::Camera, Component)
	public:
		/// @brief Default class constructor.
		Camera(bool isMain = true);
		/// @brief Class constructor.
		Camera(std::string name, bool isMain = true);
		/// @brief Class deconstructor.
		~Camera();

	private:
		/// @brief Main render camera.
		static Camera *main;

	public:
		/// @brief Camera FOV.
		FIELD(float, fov)
		/// @brief Camera near clipping plane.
		FIELD(float, nearClippingPlane)
		/// @brief Camera far clipping plane.
		FIELD(float, farClippingPlane)
		/// @brief Range the light distance the light should render till.
		FIELD(float, lightClippingPlane)

	public:
		/// @brief Get the main camera.
		/// @return The current main render camera.
		static Camera *Main();
		/// @brief Set the main Camera. `WARNING`: This method does not delete the current main camera from memory.
		/// @param camera
		static void SetMainCamera(Camera *camera);

	public:
		/// @brief Get this Camera's world position.
		/// @return World position.
		Vector3 getPosition();
		Vector3 getForward();
		Vector3 getUp();
		/// @brief Get this Camera's view matrix.
		/// @return View matrix.
		Transform getViewMatrix();
		/// @brief Get this Camera's projection matrix.
		/// @return Projection matrix.
		Transform getProjectionMatrix();
		Transform getSunViewMatrix();
		Transform getSunProjectionMatrix();
	};
}
