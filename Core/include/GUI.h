#pragma once
#include <GLAD/glad.h>

#include "imgui.h"
#include "IMGUI/backends/imgui_impl_win32.h"
#include "IMGUI/backends/imgui_impl_opengl3.h"
#include <memory>
#include <string>
#include <windef.h>

class GameObject;

class GUI
{
public:
	void Init(HWND hWindow);
	void Draw();

private:
	void DrawHierarchy();
	void DrawSelectedObjectProps();
	void DrawObjectCreator();
	void DrawConnectDialog();

	void DrawObject(std::shared_ptr<GameObject> object);

	void FrameStart();
	void FrameEnd();

	std::shared_ptr<GameObject> lastSelected;

	static std::string newObjectName;
	static std::string address;
	static std::string port;
};