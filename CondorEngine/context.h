#pragma once
class Context
{
	struct GLFWwindow* window;

public:
	bool init(int width, int height, const char* title);
	/// <summary> Update for the window. </summary>
	void tick();
	void clear();
	void terminate();
	bool shouldClose();
};

