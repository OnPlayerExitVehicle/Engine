#include "Input.h"
#include <iostream>
#include "Globals.h"
#include "MeshRenderer.h"

bool Input::inputThisFrame;

Window* Input::window;

void Input::Initialize(Window* _window)
{
	window = _window;
	//glfwSetKeyCallback(_window, OnKeyPressedCallback);
}

int monitorIndex = 0;

void Input::OnKeyPressedCallback(KeyCode key, KeyAction action)
{
	if (key == KeyCode::F10 && action == KeyAction::Press)
	{
		/*int monitorCount;
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
		glfwSetWindowMonitor(_window, useMonitor, xPos, yPos, width, height, GLFW_DONT_CARE);*/
	}
	else if(key == KeyCode::R && action == KeyAction::Press)
	{
		std::cout << "Recompiling shaders" << std::endl;
		MeshRenderer::GetDefaultShader()->Recompile();
		MeshRenderer::GetLightShader()->Recompile();
	}
}

bool Input::GetKeyDown(KeyCode key)
{
	return window->GetKeyDown(key) && !inputThisFrame;
}

bool Input::GetKey(KeyCode key)
{
	return window->GetKey(key) && !inputThisFrame;
}

bool Input::GetKeyUp(KeyCode key)
{
	return window->GetKeyUp(key) && !inputThisFrame;
}

void Input::ResetInputThisFrame()
{
	inputThisFrame = false;
}

void Input::SetInputThisFrame()
{
	inputThisFrame = true;
}