#include "GLAD/glad.h"
#include "Input.h"
#include <iostream>
#include "Globals.h"
#include "MeshRenderer.h"

bool Input::inputThisFrame;

GLFWwindow* Input::window;

void Input::Initialize(GLFWwindow* _window)
{
	window = _window;
	//glfwSetKeyCallback(_window, OnKeyPressedCallback);
}

int monitorIndex = 0;

void Input::OnKeyPressedCallback(GLFWwindow* _window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_F10 && action == GLFW_PRESS)
	{
		int monitorCount;
		GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);
		GLFWmonitor* useMonitor = nullptr;
		int xPos = 50, yPos = 50, width, height;
		if(monitorIndex >= monitorCount)
		{
			monitorIndex = 0;
			width = DEFAULT_WINDOW_WIDTH;
			height = DEFAULT_WINDOW_HEIGHT;
		}
		else
		{
			useMonitor = monitors[monitorIndex++];
			std::cout << "Switching to fullscreen on monitor = " << glfwGetMonitorName(useMonitor) << std::endl;
			glfwGetMonitorWorkarea(useMonitor, &xPos, &yPos, &width, &height);
		}
		WINDOW_WIDTH = width;
		WINDOW_HEIGHT = height;
		glViewport(xPos, yPos, width, height);
		glfwSetWindowMonitor(_window, useMonitor, xPos, yPos, width, height, GLFW_DONT_CARE);
		/*glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);*/
	}
	else if(key == GLFW_KEY_R && action == GLFW_PRESS)
	{
		std::cout << "Recompiling shaders" << std::endl;
		MeshRenderer::GetDefaultShader()->Recompile();
		MeshRenderer::GetLightShader()->Recompile();
	}
}

bool Input::GetKeyDown(KeyCode key)
{
	return false; //?
}

bool Input::GetKey(KeyCode key)
{
	return (glfwGetKey(window, (int)key) == GLFW_PRESS) && !inputThisFrame;
}

bool Input::GetKeyUp(KeyCode key)
{
	return (glfwGetKey(window, (int)key) == GLFW_RELEASE) && !inputThisFrame;
}

void Input::ResetInputThisFrame()
{
	inputThisFrame = false;
}

void Input::SetInputThisFrame()
{
	inputThisFrame = true;
}