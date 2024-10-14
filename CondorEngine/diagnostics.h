#pragma once
// third party
#include "glew/glew.h"

namespace CondorEngine {
	class diagnostics
	{
	public:
		/// @brief Print environment info to the console.
		static void Environment();
		/// @brief OpenGL error message callback.
		/// @param source 
		/// @param type 
		/// @param id 
		/// @param severity 
		/// @param length 
		/// @param message 
		/// @param userParam 
		/// @return 
		static void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
	};
};
