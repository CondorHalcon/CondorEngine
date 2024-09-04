#include "context.h"
#define GLEW_STATIC // if preprocessor not defined
#include "glew/glew.h"
#include "glfw/glfw3.h"
#include "diagnostics.h"

bool Context::init(int width, int height, const char* title)
{
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
	glEnable(GL_CULL_FACE); // optimization featues

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL); // depth testing for deciding which objects are infront of one another
	glFrontFace(GL_CCW); // winding order for determining which direction the normal is on a triangle
	glCullFace(GL_BACK);

	// enable OpenGL debug output
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(CondorEngine::diagnostics::MessageCallback, 0);

	glClearColor(.4f, .4f, .4f, 1);
	return true;
}

void Context::tick()
{
	glfwSwapBuffers(window); // swap frame buffer
	glfwPollEvents(); // poll hardware inputs
}

void Context::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the sceen buffer and the depth buffer each frame
}

void Context::terminate()
{
	glfwDestroyWindow(window);
	window = nullptr;
	glfwTerminate();
}

bool Context::shouldClose()
{
	return glfwWindowShouldClose(window) || glfwGetKey(window, GLFW_KEY_ESCAPE);
}
