#pragma once
#include "core.h"
#include "math.h"

using CondorEngine::Scene;

/// @brief Application handler class for window, active scene, and input.
class Application
{
	/// @brief Application window.
	struct GLFWwindow* window;
private:
	/// @brief Class constructor.
	Application();
	/// @brief Class deconstructor.
	~Application();
	/// @brief Class singleton.
	static Application* instance;
public:
	/// @brief Get class singleton. (Creates a new application if one doesn't already exist.)
	/// @return Class singleton.
	static Application* Instance();
	/// @brief While application should run.
	void Run();
private:
	int windowWidth;
	int windowHeight;
public:
	/// @brief Get application window dimensions.
	/// @return Window width and height as an integer vector 2.
	CondorEngine::Vector2Int getWindowDimensions();
	/// @brief Color to clear the screen buffer.
	CondorEngine::ColorRGB clearColor;
public:
	/// @brief Instantiate a new window.
	/// @param width Set the window's width.
	/// @param height Set the window's height.
	/// @param title Set the window's title.
	/// @return True if initialization was successful.
	bool init(int width, int height, const char* title);
	/// @brief Update for the window and frame buffers.
	void tick();
	/// @brief Clear screen and depth buffers.
	void clear();
	/// @brief Application Update call. (Updates active scene.)
	void update();
	/// @brief Application fixed update call.
	void fixedUpdate();
	/// @brief Application LateUpdate call. (Late updates active scene.)
	void lateUpdate();
	/// @brief Application termination.
	void terminate();
	/// @brief Check termination conditions.
	/// @return True if the application should terminate.
	bool shouldClose();

public:
	/// @brief Current active scene the application will update.
	static Scene* activeScene;
	/// @brief Check hardware input.
	/// @param key The key to check.
	/// @return True if the key has been pressed.
	static bool Input(int key);
};

