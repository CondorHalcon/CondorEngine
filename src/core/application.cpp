#include "CondorEngine/application.h"
// third party
#define GLEW_STATIC // if preprocessor not defined
#include "glew.h"
#include "glfw/glfw3.h"
// internal
#include "CondorEngine/debug.hpp"
#include "CondorEngine/time.hpp"
#include "CondorEngine/physics.h"
#include "CondorEngine/rendering/renderer.h"
#include "CondorEngine/resourcemanager.h"
#include "CondorEngine/rendering/renderers/defaultrenderer.hpp"

CondorEngine::Rendering::Renderer* CondorEngine::Application::renderer = nullptr;
CondorEngine::Scene* CondorEngine::Application::activeScene = nullptr;
CondorEngine::Application* CondorEngine::Application::instance = nullptr;
std::vector<std::string> CondorEngine::Application::layerNames = std::vector<std::string>{ "Default" };

CondorEngine::Application::Application()
{
	this->window = nullptr;
	this->windowWidth = 640;
	this->windowHeight = 480;
}

CondorEngine::Application::~Application()
{
	if (instance == this) { instance = nullptr; }
}

CondorEngine::Application* CondorEngine::Application::Instance()
{
	if (instance == nullptr)
	{
		instance = new Application();
	}
	return instance;
}

void CondorEngine::Application::runtime()
{
	while (!this->shouldClose())
	{
		// frame reset
		this->tick();

		try {
			// fixed update
			Time::accumulatedFixedTime += Time::deltaTime();
			while (Time::accumulatedFixedTime >= Time::fixedTimeStep) {
				this->fixedUpdate();
				Physics::PhysicsUpdate();
				Time::accumulatedFixedTime -= Time::fixedTimeStep;
			}

			// update
			this->update();
			this->lateUpdate();

			// draw frame
			renderer->Render();
		}
		catch (const char* msg) {
			Debug::LogError(msg);
		}

		// time update
		Time::timeUpdate();
	}
}

std::vector<std::string> CondorEngine::Application::GetLayers(unsigned int layerMask) {
	std::vector<std::string> names = std::vector<std::string>();

	for (int i = 0; i < layerNames.size(); i++) {
		unsigned int layer = (unsigned int)glm::pow(2, i);
		if (layer & layerMask) {
			names.push_back(layerNames[i]);
		}
	}

	return names;
}

CondorEngine::Vector2Int CondorEngine::Application::getWindowDimensions()
{
	return Vector2Int{ windowWidth, windowHeight };
}

bool CondorEngine::Application::init(int width, int height, const char* title)
{
	Debug::init();
	Time::timeInit();
	Debug::Log("CondorEngine::Application :: Application initializing...");

	// window handling
	// TODO: add error handling
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);   // disable window resizing
	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	glfwMakeContextCurrent(window);

	windowWidth = width;
	windowHeight = height;

	// setup graphics pipeline
	if (renderer == nullptr) {
		renderer = new Rendering::DefaultRenderer();
	}
	renderer->init();

	return true;
}

void CondorEngine::Application::tick()
{
	glfwSwapBuffers(window); // swap frame buffer
	glfwPollEvents();		 // poll hardware inputs
}

void CondorEngine::Application::update()
{
	if (activeScene != nullptr)
	{
		if (activeScene->enabled)
		{
			activeScene->HierarchyUpdate();
		}
	}
}

void CondorEngine::Application::fixedUpdate()
{
	if (activeScene != nullptr)
	{
		if (activeScene->enabled)
		{
			activeScene->HierarchyFixedUpdate();
		}
	}
}

void CondorEngine::Application::lateUpdate()
{
	if (activeScene != nullptr)
	{
		if (activeScene->enabled)
		{
			activeScene->HierarchyLateUpdate();
		}
	}
}

void CondorEngine::Application::terminate()
{
	Debug::Log("CondorEngine::Application :: Application terminating...");

	ResourceManager::cleanup();

	glfwDestroyWindow(window);
	window = nullptr;
	glfwTerminate();
}

bool CondorEngine::Application::shouldClose()
{
	return glfwWindowShouldClose(window) || glfwGetKey(window, GLFW_KEY_ESCAPE);
}

bool CondorEngine::Application::Input(int key)
{
	return glfwGetKey(Instance()->window, key);
}
