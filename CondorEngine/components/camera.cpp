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
	return this->getSceneObject() != nullptr ? this->getSceneObject()->getPosition() : Vector3{0, 0, 3};
}

CondorEngine::Transform CondorEngine::Camera::getViewMatrix()
{
	bool isValidObject = this->getSceneObject() != nullptr;
	Transform t = isValidObject ? this->getSceneObject()->getTransform() : glm::identity<Transform>();
	Vector3 forward = isValidObject ? this->getSceneObject()->getForward() : Math::TransformForward(t);
	Debug::Log(CondorEngine::to_string(forward));
	t = Math::TransformTranslate(t, -forward);
	Vector3 lookPos; Quaternion rot; Vector3 scale;
	Math::TransformSplit(t, lookPos, rot, scale);
    return glm::lookAt(
		getPosition(), // camera position
		lookPos, // look at postion
		Vector3{ 0,1,0 }); // up vector
}

CondorEngine::Transform CondorEngine::Camera::getProjectionMatrix()
{
	Vector2 windowDimentions = Application::Instance()->getWindowDimentions();
    return glm::perspective(glm::radians(60.0f),  windowDimentions.x/ (float)windowDimentions.y, .01f, 10.0f);
}
