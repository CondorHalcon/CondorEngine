#include "CondorEngine/application.h"
// third party
#define GLEW_STATIC // if preprocessor not defined
#include "glew.h"
#include "glfw/glfw3.h"
#include "CondorEngine/diagnostics.h"
// internal
#include "CondorEngine/time.hpp"
#include "CondorEngine/physics.h"
#include "CondorEngine/renderer.h"

CondorEngine::Scene *Application::activeScene = nullptr;
Application *Application::instance = nullptr;

Application::Application()
{
	this->window = nullptr;
	this->windowWidth = 640;
	this->windowHeight = 480;
	this->clearColor = CondorEngine::ColorRGB{.4, .4, .4};
}
Application::~Application()
{
	delete instance;
}

Application *Application::Instance()
{
	if (instance == nullptr)
	{
		instance = new Application();
	}
	return instance;
}

void Application::Run()
{
	while (!this->shouldClose())
	{
		// frame reset
		this->tick();
		this->clear();

		// fixed update
		CondorEngine::Time::accumulatedFixedTime += CondorEngine::Time::deltaTime();
		while (CondorEngine::Time::accumulatedFixedTime >= CondorEngine::Time::fixedTimeStep)
		{
			this->fixedUpdate();
			CondorEngine::Physics::PhysicsUpdate();
			CondorEngine::Time::accumulatedFixedTime -= CondorEngine::Time::fixedTimeStep;
		}

		// update
		this->update();
		this->lateUpdate();

		// draw frame
		CondorEngine::Renderer::Render();

		// time update
		CondorEngine::Time::timeUpdate();
	}
}

CondorEngine::Vector2Int Application::getWindowDimensions()
{
	return CondorEngine::Vector2Int{windowWidth, windowHeight};
}

bool Application::init(int width, int height, const char *title)
{
	CondorEngine::Time::timeInit();

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
	glDebugMessageCallback(CondorEngine::diagnostics::MessageCallback, 0);

	glClearColor(.4f, .4f, .4f, 1);
	return true;
}

void Application::tick()
{
	glfwSwapBuffers(window); // swap frame buffer
	glfwPollEvents();		 // poll hardware inputs
}

void Application::clear()
{
	glClearColor(clearColor.r, clearColor.g, clearColor.b, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the screen buffer and the depth buffer each frame
}

void Application::update()
{
	if (activeScene != nullptr)
	{
		if (activeScene->enabled)
		{
			activeScene->HierarchyUpdate();
		}
	}
}

void Application::fixedUpdate()
{
	if (activeScene != nullptr)
	{
		if (activeScene->enabled)
		{
			activeScene->HierarchyFixedUpdate();
		}
	}
}
void Application::lateUpdate()
{
	if (activeScene != nullptr)
	{
		if (activeScene->enabled)
		{
			activeScene->HierarchyLateUpdate();
		}
	}
}

void Application::terminate()
{
	glfwDestroyWindow(window);
	window = nullptr;
	glfwTerminate();
}

bool Application::shouldClose()
{
	return glfwWindowShouldClose(window) || glfwGetKey(window, GLFW_KEY_ESCAPE);
}

bool Application::Input(int key)
{
	return glfwGetKey(Instance()->window, key);
}
