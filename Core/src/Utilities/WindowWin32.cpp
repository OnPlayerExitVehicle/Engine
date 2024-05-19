#include "Window.h"
#define WIN32_LEAN_AND_MEAN
#define UNICODE
#include <Windows.h>
#include <cassert>
#include <GLAD/glad.h>

#if WIN32

Window* Window::instance = nullptr;

LRESULT CALLBACK WindowProc(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	default:
		return DefWindowProc(hWindow, msg, wParam, lParam);
	}
}

void Window::Create(int width, int height, const std::string& title)
{
	instance = this;
	WNDCLASSEX wClass = {
		sizeof(WNDCLASSEX),
		CS_OWNDC,
		WindowProc,
		0,
		0,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		std::wstring(L"EngineWindowClass").c_str()
	};

	ATOM wClassAtom = RegisterClassEx(&wClass);
	assert(wClassAtom);

	HWND hWindow = CreateWindow(
		MAKEINTATOM(wClassAtom),
		std::wstring(title.begin(), title.end()).c_str(),
		WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		NULL,
		NULL,
		NULL,
		NULL
	);
	assert(hWindow);

	(void)ShowWindow(hWindow, SW_SHOW);
	handle = hWindow;
}

void Window::InitializeGraphicsContext()
{
	HGLRC glContext = wglCreateContext((HDC)hardwareDeviceContext);
	wglMakeCurrent((HDC)hardwareDeviceContext, glContext);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
}

void Window::SetWindowPFD()
{
	HDC hdc = GetDC((HWND)handle);
	PIXELFORMATDESCRIPTOR pfd {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		24,
		8,
		0,
		PFD_MAIN_PLANE,
		0, 0, 0, 0
	};

	int pfi = ChoosePixelFormat(hdc, &pfd);
	assert(pfi);

	BOOL result = SetPixelFormat(hdc, pfi, &pfd);
	assert(result);

	hardwareDeviceContext = hdc;
}

bool Window::ProcessLoop()
{
	MSG msg;
	BOOL ret;

	ret = GetMessage(&msg, (HWND)handle, 0, 0);

	if(ret >= 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		SwapBuffers((HDC)hardwareDeviceContext);
		return true;
	}

	return false;
}

void Window::SetKeyCallback(std::function<void(KeyCode, KeyAction)> func)
{
	//TODO
}

bool Window::GetKeyDown(KeyCode key) { return false; }
bool Window::GetKey(KeyCode key) { return false; }
bool Window::GetKeyUp(KeyCode key) { return false; }

#endif