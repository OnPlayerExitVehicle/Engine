#pragma once
#include "Scene.h"
#include <string>
#include "GLFW/include/GLFW/glfw3.h"
#include <thread>

class Engine
{
private:
	GLFWwindow* window;
	Scene* scene;
	std::thread loopThread;

	void InitWindow(int windowWidth, int windowHeight);
	void InitGraphics();
	void InitDefaultBehaviour();

public:
	Engine(int windowWidth, int windowHeight);
	void EngineLoop();
};