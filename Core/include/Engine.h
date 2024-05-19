#pragma once
#include "Scene.h"
#include <string>
#include <thread>
#include "Window.h"

class Engine
{
private:
	Window window;
	Scene* scene;
	std::thread loopThread;

	void InitWindow(int windowWidth, int windowHeight);
	void InitGraphics();
	void InitDefaultBehaviour();

public:
	Engine(int windowWidth, int windowHeight);
	void EngineLoop();
};