#pragma once

#include "../utils/imgui/imgui.h"
#include "../utils/imgui/imgui_impl_glfw.h"
#include "../utils/imgui/imgui_impl_opengl3.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "gamelogic.h"
#include "renderer.h"
#include "modelmanager.h"
#include "scene.h"

#include "../utils/modelloader.h"
#include "../utils/shader.h"
#include "../utils/camera_freefloat.h"
#include "../utils/camera_isometric.h"
#include "../utils/texture_2d.h"
#include "../utils/texture_cubemap.h"
#include "../utils/texture_rendertarget.h"
#include "../utils/debug.h"

#include <fstream>
#include <sstream>
#include <map>



class Application {

public:
	Application(GameSettings _settings);


	bool runApplication();
	bool stopApplication();

	void processInput(GLFWwindow* _window);
	void process_resize(GLFWwindow* _window, int _width, int _height);
	void process_mouse(GLFWwindow* _window, double _xpos, double _ypos);
	void process_scroll(GLFWwindow* _window, double _xoffset, double _yoffset);

	GLFWwindow* getWindow() { return m_window; }
	GameLogic* getGameLogic() { return m_gameLogic;  }


private: 
	// game settings
	// -------------
	GameSettings m_settings;
	GameLogic* m_gameLogic;

	// window
	// -------------
	GLFWwindow* m_window;

	// preparation
	// -------------
	bool setupWindow(unsigned int _width, unsigned int _height);
	bool setupModels();


	// gamestate
	// -------------
	unsigned int viewProjectionBuffer;
	unsigned int timeBuffer;
	unsigned int dirLightBuffer;
	unsigned int clippingPlaneBuffer;
	unsigned int cameraBuffer;

	// water variables
	const unsigned int REFLECTION_WIDTH = m_settings.SCR_WIDTH;
	const unsigned int REFLECTION_HEIGHT = m_settings.SCR_HEIGHT;
	const unsigned int REFRACTION_WIDTH = m_settings.SCR_WIDTH;
	const unsigned int REFRACTION_HEIGHT = m_settings.SCR_HEIGHT;

	// debugging
	// -------------
	void fillImGui();
	void enablePolygonMode();

	// timing
	// -------------
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	// renderer instance
	// -------------
	Renderer* m_renderer;

	// debugger instance - starts in SetupApplication()
	// -------------
	glDebugger* m_debugger;

	// camera instance
	// -------------
	Camera* m_camera;
	float lastX = (float)m_settings.SCR_WIDTH / 2.0;
	float lastY = (float)m_settings.SCR_HEIGHT / 2.0;
	bool firstMouse = true;

	// controls
	// -------------
	double lastCursorToggle = 0.0f;				// notes time tab was pressed the last time
	const double cursorToggleDelay = 1.0f;		// the delay between toggling cursor
	bool cursorEnabled = false;

	// utility
	bool clearBufferBits();
	bool resetTesting();
};

