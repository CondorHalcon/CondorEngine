#include "camera.h"
#include "math.h"

CondorEngine::Camera* CondorEngine::Camera::instance = nullptr;

CondorEngine::Camera::Camera() {
	this->position = Vector3{ 0,0,3 };
	this->viewMatrix = glm::lookAt(
		position, // camera position
		Vector3{ 0,0,0 }, // look at postion
		Vector3{ 0,1,0 }); // up vector
	this->projectionMatrix = glm::perspective(glm::radians(60.0f), 640 / (float)480, .01f, 10.0f);
}
CondorEngine::Camera::~Camera()
{
	delete instance;
}

void CondorEngine::Camera::Init(Vector3 pos, Vector3 lookAt)
{
	delete instance;
	Instance();
	SetPositionAndLookAt(pos, lookAt);
}

CondorEngine::Camera* CondorEngine::Camera::Instance()
{
	if (instance == nullptr) {
		instance = new Camera();
	}
	return instance;
}

void CondorEngine::Camera::SetPositionAndLookAt(Vector3 pos, Vector3 lookAt)
{
	SetPosition(pos);
	LookAt(lookAt);
}

void CondorEngine::Camera::SetPosition(Vector3 pos)
{
	Camera* cam = Instance();
	cam->position = pos;
}

void CondorEngine::Camera::LookAt(Vector3 lookAt)
{
	Camera* cam = Instance();
	instance->viewMatrix = glm::lookAt(
		instance->position, // camera position
		lookAt, // look at postion
		Vector3{ 0,1,0 }); // up vector
}
