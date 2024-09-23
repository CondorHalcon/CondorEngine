#pragma once
// std
#include <string>
#include <iostream>

namespace CondorEngine {
	class Debug
	{
	public:
		static void Log(const char* msg) {
			std::cout << "\nINFO: " << msg << std::endl;
		}
		static void Log(std::string msg) {
			Log(msg.c_str());
		}
		static void LogWarning(const char* msg) {
			std::cout << "\nWARNING: " << msg << std::endl;
		}
		static void LogWarning(std::string msg) {
			Log(msg.c_str());
		}
		static void LogError(const char* msg) {
			std::cout << "\nERROR: " << msg << std::endl;
		}
		static void LogError(std::string msg) {
			Log(msg.c_str());
		}
	};
}

