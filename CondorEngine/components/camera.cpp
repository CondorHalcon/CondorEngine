#include "camera.h"
#include "../math.h"
#include "../core.h"
#include "../application.h"

#include "../debug.h"

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
	return this->getSceneObject()->getPosition();
}

CondorEngine::Transform CondorEngine::Camera::getViewMatrix()
{
    return glm::lookAt(
		this->getSceneObject()->getPosition(), // camera position
		this->getSceneObject()->getPosition() + this->getSceneObject()->getForward(), // look at postion
		this->getSceneObject()->getUp()); // up vector
}

CondorEngine::Transform CondorEngine::Camera::getProjectionMatrix()
{
	Vector2Int windowDimensions = Application::Instance()->getWindowDimensions();
    return glm::perspective(glm::radians(fov), windowDimensions.x/ (float)windowDimensions.y, nearClippingPlane, farClippingPlane);
}
