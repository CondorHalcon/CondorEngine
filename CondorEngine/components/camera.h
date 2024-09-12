#pragma once
#include "../math.h"
#include "../core.h"
// third party
#include "glm/ext.hpp"
#include "glfw/glfw3.h"

namespace CondorEngine {
	class Camera : public Component
	{
	public:
		Camera();
		~Camera();
	private:
		static Camera* main;

	public:
		/// <summary> Get the main camera; </summary>
		/// <returns></returns>
		static Camera* Main();
		/// <summary> Set the main Camera. WARNING: This method does not delete the current main camera from memory. </summary>
		/// <param name="camera"></param>
		static void SetMainCamera(Camera* camera);

	public:
		Vector3 getPosition();
		Transform getViewMatrix();
		Transform getProjectionMatrix();
	};
}

