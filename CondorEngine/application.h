#pragma once
#include "core.h"
using CondorEngine::Scene;

class Application
{
	struct GLFWwindow* window;

public:
	/// <summary> Instatiate a new window. </summary>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <param name="title"></param>
	/// <returns></returns>
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

