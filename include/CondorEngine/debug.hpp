#pragma once
// std
#include <string>
#include <iostream>

namespace CondorEngine {
	/// @brief Debugging utility class.
	class Debug
	{
	public:
		/// @brief Print an `INFO` message to console.
		/// @param msg Message to print.
		static void Log(const char* msg) {
			std::cout << "\nINFO: " << msg << std::endl;
		}
		/// @brief Print an `INFO` message to console.
		/// @param msg Message to print.
		static void Log(std::string msg) {
			Log(msg.c_str());
		}
		/// @brief Print a `WARNING` message to console.
		/// @param msg Message to print.
		static void LogWarning(const char* msg) {
			std::cout << "\nWARNING: " << msg << std::endl;
		}
		/// @brief Print a `WARNING` message to console.
		/// @param msg Message to print.
		static void LogWarning(std::string msg) {
			Log(msg.c_str());
		}
		/// @brief Print an `ERROR` message to console.
		/// @param msg Message to print.
		static void LogError(const char* msg) {
			std::cout << "\nERROR: " << msg << std::endl;
		}
		/// @brief Print an `ERROR` message to console.
		/// @param msg Message to print.
		static void LogError(std::string msg) {
			Log(msg.c_str());
		}
	};
}

