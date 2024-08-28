#include "camera.h"

Camera* Camera::instance = nullptr;

Camera::Camera() {
	this->position = vec3{ 0,0,3 };
	this->viewMatrix = glm::lookAt(
		position, // camera position
		vec3{ 0,0,0 }, // look at postion
		vec3{ 0,1,0 }); // up vector
	this->projectionMatrix = glm::perspective(glm::radians(60.0f), 640 / (float)480, .01f, 10.0f);
}
Camera::~Camera()
{
	delete instance;
}

void Camera::Init(vec3 pos, vec3 lookAt)
{
	delete instance;
	Instance();
	SetPositionAndLookAt(pos, lookAt);
}

Camera* Camera::Instance()
{
	if (instance == nullptr) {
		instance = new Camera();
	}
	return instance;
}

void Camera::SetPositionAndLookAt(vec3 pos, vec3 lookAt)
{
	SetPosition(pos);
	LookAt(lookAt);
}

void Camera::SetPosition(vec3 pos)
{
	Camera* cam = Instance();
	cam->position = pos;
}

void Camera::LookAt(vec3 lookAt)
{
	Camera* cam = Instance();
	instance->viewMatrix = glm::lookAt(
		instance->position, // camera position
		lookAt, // look at postion
		vec3{ 0,1,0 }); // up vector
}
