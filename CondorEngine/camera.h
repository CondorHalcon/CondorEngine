#pragma once
#include "math.h"
// thirdparty
#include "glm/ext.hpp"
#include "glfw/glfw3.h"

namespace CondorEngine {
	class Camera
	{
	private:
		Camera();
		~Camera();
		static Camera* instance;

	public:
		static void Init(Vector3 pos, Vector3 lookAt);
		static Camera* Instance();
		static void SetPositionAndLookAt(Vector3 pos, Vector3 lookAt);
		static void SetPosition(Vector3 pos);
		static void LookAt(Vector3 lookAt);

	public:
		Vector3 position;
		Transform viewMatrix;
		Transform projectionMatrix;
	};
}

