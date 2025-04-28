#include "CondorEngine/components/camera.h"
// internal
#include "CondorEngine/debug.hpp"
#include "CondorEngine/application.h"
#include "CondorEngine/sceneobject.h"

CondorEngine::Camera *CondorEngine::Camera::main = nullptr;

CondorEngine::Camera::Camera()
{
	this->name = "CondorEngine::Camera";
	if (Camera::main == nullptr)
	{
		Camera::main = this;
	}
}
CondorEngine::Camera::~Camera()
{
	if (this == Camera::main)
	{
		Camera::main = nullptr;
	}
}

CondorEngine::Camera *CondorEngine::Camera::Main()
{
	return Camera::main;
}

void CondorEngine::Camera::SetMainCamera(Camera *camera)
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
		this->getSceneObject()->getPosition(),										  // camera position
		this->getSceneObject()->getPosition() + this->getSceneObject()->getForward(), // look at postion
		this->getSceneObject()->getUp());											  // up vector
}

CondorEngine::Transform CondorEngine::Camera::getProjectionMatrix()
{
	Vector2Int windowDimensions = Application::Instance()->getWindowDimensions();
	return glm::perspective(glm::radians(fov), windowDimensions.x / (float)windowDimensions.y, nearClippingPlane, farClippingPlane);
}

CondorEngine::Transform CondorEngine::Camera::getSunViewMatrix() {
	Vector3 position = getPosition();
	Vector3 direction = Application::activeScene ? Application::activeScene->light.direction : Vector3{ 0.f, -1.f, 0.f };
	return glm::lookAt(
		position, // light position
		position + direction, // look at position
		Vector3{ 0.0f, 1.0f, 0.0f } // up vector
	);
}

CondorEngine::Transform CondorEngine::Camera::getSunProjectionMatrix() {
	return glm::ortho(-lightClippingPlane, lightClippingPlane, -lightClippingPlane, lightClippingPlane,
		-lightClippingPlane, lightClippingPlane);
}
