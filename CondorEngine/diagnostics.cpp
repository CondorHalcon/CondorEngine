#include "diagnostics.h"
// std
#include <iostream>
// third party
#include "glew/glew.h"

void CondorEngine::diagnostics::Environment()
{
	std::cout << "OpenGL version: " << (const char*)glGetString(GL_VERSION) << std::endl;
	std::cout << "GLEW version: " << (const char*)glewGetString(GLEW_VERSION) << std::endl;

	std::cout << "Renderer: " << (const char*)glGetString(GL_RENDERER) << std::endl;
	std::cout << "GLSL: " << (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

void GLAPIENTRY CondorEngine::diagnostics::MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	std::cout << std::endl;
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}
