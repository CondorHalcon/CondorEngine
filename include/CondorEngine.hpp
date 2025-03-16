#pragma once
#include "CondorEngine/pch.h"

// engine core
#include "CondorEngine/application.h"
#include "CondorEngine/component.h"
#include "CondorEngine/debug.hpp"
#include "CondorEngine/material.h"
#include "CondorEngine/math.hpp"
#include "CondorEngine/object.h"
#include "CondorEngine/physics.h"
#include "CondorEngine/renderer.h"
#include "CondorEngine/scene.h"
#include "CondorEngine/sceneobject.h"
#include "CondorEngine/time.hpp"

//namespace CondorEngine
//{
extern "C" int DllExport RunApplication(Application* app, const char* title, CondorEngine::Vector2 resolution);
//}