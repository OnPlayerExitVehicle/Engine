﻿#define WIN32_LEAN_AND_MEAN

#include "Globals.h"
#include "Engine.h"

#if WIN32
int WinMain(
  HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  LPSTR     lpCmdLine,
  int       nShowCmd
)
{
	std::cout << "WinMain" << std::endl;
	Engine engine(WINDOW_WIDTH, WINDOW_HEIGHT);
	engine.EngineLoop();
}
#endif

int main()
{
	std::cout << "main" << std::endl;
	Engine engine(WINDOW_WIDTH, WINDOW_HEIGHT);
	engine.EngineLoop();
}