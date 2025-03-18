#include "CondorEngine/application.h"
// third party
#define GLEW_STATIC // if preprocessor not defined
#include "glew.h"
#include "glfw/glfw3.h"
// internal
#include "CondorEngine/debug.hpp"
#include "CondorEngine/time.hpp"
#include "CondorEngine/physics.h"
#include "CondorEngine/renderer.h"
#include "CondorEngine/resourcemanager.h"

CondorEngine::Scene* CondorEngine::Application::activeScene = nullptr;
CondorEngine::Application* CondorEngine::Application::instance = nullptr;

CondorEngine::Application::Application()
{
	this->window = nullptr;
	this->windowWidth = 640;
	this->windowHeight = 480;
	this->clearColor = ColorRGB{ .4, .4, .4 };
}
CondorEngine::Application::~Application()
{
	delete instance;
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
		this->clear();

		// fixed update
		Time::accumulatedFixedTime += Time::deltaTime();
		while (Time::accumulatedFixedTime >= Time::fixedTimeStep)
		{
			this->fixedUpdate();
			Physics::PhysicsUpdate();
			Time::accumulatedFixedTime -= Time::fixedTimeStep;
		}

		// update
		this->update();
		this->lateUpdate();

		// draw frame
		Renderer::Render();

		// time update
		Time::timeUpdate();
	}
}

CondorEngine::Vector2Int CondorEngine::Application::getWindowDimensions()
{
	return Vector2Int{ windowWidth, windowHeight };
}

bool CondorEngine::Application::init(int width, int height, const char* title)
{
	Time::timeInit();
	Debug::init();

	this->windowWidth = width;
	this->windowHeight = height;
	// window handling
	// TODO: add error handling
	glfwInit();
	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	glfwMakeContextCurrent(window);
	// start setting up graphics pipeline
	glewInit();
	// set flags for openGL features
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE); // optimization features

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL); // depth testing for deciding which objects are in front of one another
	glFrontFace(GL_CCW);	// winding order for determining which direction the normal is on a triangle
	glCullFace(GL_BACK);

	// enable OpenGL debug output
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(Debug::GLMessageCallback, 0);

	glClearColor(.4f, .4f, .4f, 1);

	std::string message = "Application :: [OpenGL Environment]\n";
	message.append("\t- OpenGL version: " + std::string((const char*)glGetString(GL_VERSION)) + "\n");
	message.append("\t- GLEW version: " + std::string((const char*)glewGetString(GLEW_VERSION)) + "\n");
	message.append("\t- Renderer: " + std::string((const char*)glGetString(GL_RENDERER)) + "\n");
	message.append("\t- GLSL: " + std::string((const char*)glGetString(GL_SHADING_LANGUAGE_VERSION)));
	Debug::Log(message);

	return true;
}

void CondorEngine::Application::tick()
{
	glfwSwapBuffers(window); // swap frame buffer
	glfwPollEvents();		 // poll hardware inputs
}

void CondorEngine::Application::clear()
{
	glClearColor(clearColor.r, clearColor.g, clearColor.b, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the screen buffer and the depth buffer each frame
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
