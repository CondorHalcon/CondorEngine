#pragma once
#include "glew/glew.h"

namespace diagnostics
{
	void Environment();
	void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
};

