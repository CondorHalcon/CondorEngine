#include "camera.h"
#include "../math.h"
#include "../core.h"

CondorEngine::Camera* CondorEngine::Camera::main = nullptr;

CondorEngine::Camera::Camera() {
	this->name = "CondorEngine::Camera";
	if (Camera::main == nullptr) {
		Camera::main = this;
	}
}
CondorEngine::Camera::~Camera()
{
	if (this == Camera::main) {
		Camera::main = nullptr;
	}
}

CondorEngine::Camera* CondorEngine::Camera::Main()
{
	return Camera::main;
}

void CondorEngine::Camera::SetMainCamera(Camera* camera)
{
	Camera::main = camera;
}

CondorEngine::Vector3 CondorEngine::Camera::getPosition()
{
	return this->getSceneObject() != nullptr ? this->getSceneObject()->getPosition() : Vector3{0, 0, 3};
}

CondorEngine::Transform CondorEngine::Camera::getViewMatrix()
{
    return glm::lookAt(
		getPosition(), // camera position
		Vector3{ 0,0,0 }, // look at postion
		Vector3{ 0,1,0 }); // up vector
}

CondorEngine::Transform CondorEngine::Camera::getProjectionMatrix()
{
    return glm::perspective(glm::radians(60.0f), 640 / (float)480, .01f, 10.0f);
}
