#define WIN32_LEAN_AND_MEAN

#include "Globals.h"
#include "Engine.h"

int main()
{
	Engine engine(WINDOW_WIDTH, WINDOW_HEIGHT);

	engine.EngineLoop();
}