#pragma once
#include "core.h"
using CondorEngine::Scene;

class Application
{
	struct GLFWwindow* window;

public:
	bool init(int width, int height, const char* title);
	/// <summary> Update for the window. </summary>
	void tick();
	void clear();
	void update();
	void lateUpdate();
	void terminate();
	bool shouldClose();
public:
	static Scene* activeScene;
};

