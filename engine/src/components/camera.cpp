#include "CondorEngine/components/camera.h"
// internal
#include "CondorEngine/debug.hpp"
#include "CondorEngine/application.h"
#include "CondorEngine/sceneobject.h"

CondorEngine::Camera *CondorEngine::Camera::main = nullptr;

CondorEngine::Camera::Camera(bool isMain) : Camera("Camera", isMain) {}

CondorEngine::Camera::Camera(std::string name, bool isMain) : Component(name) {
	if (Camera::main == nullptr && isMain) {
		Camera::main = this;
	}

	this->fov = 60.0f;
	this->nearClippingPlane = .01f;
	this->farClippingPlane = 100.0f;
	this->lightClippingPlane = 20.0f;
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
	return this->getSceneObject() != nullptr ? this->getSceneObject()->getPosition() : Vector3{};
}

CondorEngine::Vector3 CondorEngine::Camera::getForward() {
	return this->getSceneObject() != nullptr ? this->getSceneObject()->getForward() : Vector3{ 0, 0, 1 };
}

CondorEngine::Vector3 CondorEngine::Camera::getUp() {
	return this->getSceneObject() != nullptr ? this->getSceneObject()->getUp() : Vector3{ 0, 1, 0 };
}

CondorEngine::Transform CondorEngine::Camera::getViewMatrix()
{
	return glm::lookAt(
		getPosition(),					// camera position
		getPosition() + getForward(),	// look at postion
		getUp());						// up vector
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
