#define WIN32_LEAN_AND_MEAN

#include "Globals.h"
#include "Engine.h"

int WinMain(
  _In_ HINSTANCE hInstance,
  _In_ HINSTANCE hPrevInstance,
  _In_ LPSTR     lpCmdLine,
  _In_ int       nShowCmd
)
{
	Engine engine(WINDOW_WIDTH, WINDOW_HEIGHT);
	engine.EngineLoop();
}

//int main()
//{
//	Engine engine(WINDOW_WIDTH, WINDOW_HEIGHT);
//	engine.EngineLoop();
//}