#pragma once

#ifdef CondorEngine_EXPORTS
#define DllExport __declspec(dllexport)
#else
#define DllExport __declspec(dllimport)
#endif

#define GLEW_STATIC // if preprocessor not defined
#include <glew.h>
#include <glfw/glfw3.h>

#include <stdexcept>
