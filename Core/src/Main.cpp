#define WIN32_LEAN_AND_MEAN

#include <corecrt.h>
#include <iostream>
#include <Windows.h>
#include <sstream>
#include <vector>
#include <cstring>
#include "bullet3-3.24/src/btBulletDynamicsCommon.h"
#include "Scene.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Globals.h"
#include "HTime.h"
#include "Input.h"
#include "TestComponent.h"
#include "PlaneCollider.h"
#include "BoxCollider.h"
#include "Rigidbody.h"
#include "TextureLoader.h"

GLFWwindow* window;

int main()
{
	srand(NULL);

	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	std::stringstream ss;
	ss << "Engine (" << (sizeof(void*) * 8) << " bit)";
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, ss.str().c_str(), nullptr, nullptr);
	
	if (window == nullptr)
	{
		std::cout << "Window is NULL" << std::endl;
	}
	glfwMakeContextCurrent(window);
	gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

	
	/*std::cout << "Hello Bullet" << std::endl;
	char dir[256];
	GetCurrentDirectory(256, dir);
	std::cout << dir << std::endl;*/

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	auto scene = new Scene(window);


	//auto plane = scene->CreateObject(glm::vec3(), glm::vec3(), glm::vec3(100.0f, 1.0f, 100.0f));
	auto plane = scene->CreateObject("Plane");
	plane->AddComponent<PlaneCollider>();
	plane->AddComponent<Rigidbody>();

	auto pos = Vector3(.0f, 7.0f, .0f);
	//auto rot = Quaternion(.0f);
	auto scale = Vector3(1.0f, 1.0f, 1.0f);

	
	/*for (int i = 0; i < 1000; i++)
	{
		auto cube = scene->CreateObject(pos, Quaternion(), scale);
		cube->AddComponent<MeshRenderer>();
		cube->AddComponent<BoxCollider>();
		cube->AddComponent<Rigidbody>(10.0f);
	}*/
	
	//auto texture1 = TextureLoader::LoadTexture(TEXTURES_DIRECTORY"brick.jpg");
	//auto texture2 = TextureLoader::LoadTexture(TEXTURES_DIRECTORY"container.jpg");
	//
	//auto cube = scene->CreateObject("Haydar", Vector3(0.0f, 7.0f, 0.0f));
	//cube->AddComponent<MeshRenderer>();
	//cube->AddComponent<BoxCollider>();
	//cube->AddComponent<Rigidbody>(10.0f);
	//cube->AddComponent<TestComponent>();

	//auto cube2 = scene->CreateObject("Temel", Vector3(1.0f, 0.0f, 0.0f));
	//cube2->AddComponent<MeshRenderer>(texture2);
	////cube2->transform->SetParent(cube->transform);
	//cube2->AddComponent<BoxCollider>();
	//cube2->AddComponent<Rigidbody>(10.0f);
	

	auto camera = scene->CreateObject("Camera", Vector3(0.0f, -3.0f, -10.0f));
	camera->AddComponent<Camera>();
	camera->AddComponent<TestComponent>();
	
	DEBUG_LOG("Starting Loop...");

	Input::Initialize(window);

	//auto frameStart = std::chrono::system_clock::now();
	//double secondTimer = 0.0;
	//int frameCount = 0;

	while (!glfwWindowShouldClose(window))
	{
		Time::FrameStart();
		//frameCount++;

		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		scene->Process();
		glfwSwapBuffers(window);

		//auto currentTime = std::chrono::system_clock::now();
		//double difference = std::chrono::duration<double, std::milli>(currentTime - frameStart).count();

		/*secondTimer += difference;
		if (secondTimer >= 1000.0)
		{
			secondTimer = std::fmod(secondTimer, 1000.0);
			std::cout << frameCount << " FPS" << std::endl;
			frameCount = 0;
		}
		frameStart = currentTime;*/
	}
}