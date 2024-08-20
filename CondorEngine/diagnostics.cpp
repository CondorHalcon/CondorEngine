#include "diagnostics.h"
#include "glew/glew.h"
#include <iostream>

void diagnostics::Environment()
{
	std::cout << "OpenGL version: " << (const char*)glGetString(GL_VERSION) << std::endl;
	std::cout << "GLEW version: " << (const char*)glewGetString(GLEW_VERSION) << std::endl;

	std::cout << "Renderer: " << (const char*)glGetString(GL_RENDERER) << std::endl;
	std::cout << "GLSL: " << (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}
