#pragma once
#include "glew/glew.h"

namespace CondorEngine {
	class diagnostics
	{
	public:
		static void Environment();
		static void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
	};
};
