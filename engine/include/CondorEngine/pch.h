#pragma once

#ifdef CondorEngine_EXPORTS
#define DllExport __declspec(dllexport)
#else
#define DllExport __declspec(dllimport)
#endif

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <stdexcept>
#include <string>
#include <vector>
