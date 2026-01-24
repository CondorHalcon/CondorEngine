#pragma once
#include "CondorEngine/pch.h"
// std
#include <string>
#include <iostream>

namespace CondorEngine {
	/// @brief Debugging utility class.
	class DllExport Debug
	{
	public:
		/// @brief Initialize log file.
		static void init();
		/// @brief Print an `INFO` message to console.
		/// @param msg Message to print.
		static void Log(const char* msg);
		/// @brief Print an `INFO` message to console.
		/// @param msg Message to print.
		static void Log(std::string msg);
		/// @brief Print a `WARNING` message to console.
		/// @param msg Message to print.
		static void LogWarning(const char* msg);
		/// @brief Print a `WARNING` message to console.
		/// @param msg Message to print.
		static void LogWarning(std::string msg);
		/// @brief Print an `ERROR` message to console.
		/// @param msg Message to print.
		static void LogError(const char* msg);
		/// @brief Print an `ERROR` message to console.
		/// @param msg Message to print.
		static void LogError(std::string msg);
		/// @brief OpenGL error message callback.
		/// @param source
		/// @param type
		/// @param id
		/// @param severity
		/// @param length
		/// @param message
		/// @param userParam
		/// @return
		static void GLAPIENTRY GLMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
	private:
		static bool hasInit;
		static std::string getTime();
		static void printToFile(const std::string& message);
	};
}

