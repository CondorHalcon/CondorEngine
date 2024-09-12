#pragma once
#include "core.h"
using CondorEngine::Scene;

class Application
{
	struct GLFWwindow* window;
private:
	Application();
	~Application();
	static Application* instance;
public:
	static Application* Instance();

public:
	/// <summary> Instantiate a new window. </summary>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <param name="title"></param>
	/// <returns></returns>
	bool init(int width, int height, const char* title);
	/// <summary> Update for the window. </summary>
	void tick();
	/// <summary> </summary>
	void clear();
	/// <summary> </summary>
	void update();
	/// <summary> </summary>
	void lateUpdate();
	/// <summary> </summary>
	void terminate();
	/// <summary> </summary>
	bool shouldClose();

public:
	static Scene* activeScene;
	static bool Input(int key);
};

