#pragma once
#include "glm/ext.hpp"
#include "glfw/glfw3.h"
using glm::mat4;
using glm::vec3;

namespace CondorEngine {
	class Camera
	{
	private:
		Camera();
		~Camera();
		static Camera* instance;

	public:
		static void Init(vec3 pos, vec3 lookAt);
		static Camera* Instance();
		static void SetPositionAndLookAt(vec3 pos, vec3 lookAt);
		static void SetPosition(vec3 pos);
		static void LookAt(vec3 lookAt);

	public:
		vec3 position;
		mat4 viewMatrix;
		mat4 projectionMatrix;
	};
}

