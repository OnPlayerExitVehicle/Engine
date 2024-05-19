#pragma once
#include "Singleton.h"
#include "Window.h"


class Input
{
private:
	static Window* window;
	static bool inputThisFrame;

public:
	static void Initialize(Window* window);

	static bool GetKeyDown(KeyCode key);
	static bool GetKey(KeyCode key);
	static bool GetKeyUp(KeyCode key);

	static void ResetInputThisFrame();
	static void SetInputThisFrame();

	static void OnKeyPressedCallback(KeyCode key, KeyAction action);
};