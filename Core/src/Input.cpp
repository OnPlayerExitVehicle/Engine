#include "Input.h"
#include <iostream>
#include "Globals.h"

bool Input::inputThisFrame;

GLFWwindow* Input::window;

void Input::Initialize(GLFWwindow* _window)
{
	window = _window;
	//glfwSetKeyCallback(_window, OnKeyPressedCallback);
}

void Input::OnKeyPressedCallback(GLFWwindow* _window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_F10 && action == GLFW_PRESS)
	{
		glfwSetWindowMonitor(_window, nullptr, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GLFW_DONT_CARE);
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