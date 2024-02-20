#pragma once
#include <glad/glad.h>
//#include "GLFW/include/GLFW/glfw3.h"

#include "imgui.h"
#include "IMGUI/backends/imgui_impl_glfw.h"
#include "IMGUI/backends/imgui_impl_opengl3.h"
#include <memory>
#include <string>

class GameObject;

class GUI
{
public:
	void Init(GLFWwindow* window);
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