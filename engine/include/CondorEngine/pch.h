#pragma once

#ifdef CondorEngine_EXPORTS
#define DllExport __declspec(dllexport)
#else
#define DllExport __declspec(dllimport)
#endif

#define GLAD_API_CALL DllExport
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <stdexcept>
#include <string>
#include <vector>

#ifndef CondorEngine_Serialization
#include "CondorEngine/serialization.hpp"
#endif
