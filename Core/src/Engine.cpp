#include "Engine.h"
#include "PlaneCollider.h"
#include "Input.h"
#include "Camera.h"
#include "TestComponent.h"
#include "HTime.h"
#include "Rigidbody.h"

Engine::Engine(int windowWidth, int windowHeight)
{
	srand(NULL);
	InitWindow(windowWidth, windowHeight);
	InitGraphics();

	scene = new Scene(window);
	Input::Initialize(window);

	InitDefaultBehaviour();
}

void Engine::InitWindow(int windowWidth, int windowHeight)
{
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window = glfwCreateWindow(windowWidth, windowHeight, std::format("Engine ({} bit)", sizeof(void*) * 8).c_str(), nullptr, nullptr);
	if (window == nullptr) throw std::exception("Cannot create window!");
}

void Engine::InitGraphics()
{
	glfwMakeContextCurrent(window);
	gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
}

void Engine::InitDefaultBehaviour()
{
	auto plane = scene->CreateObject("Plane");
	plane->AddComponent<PlaneCollider>();
	plane->AddComponent<Rigidbody>();

	auto camera = scene->CreateObject("Camera", Vector3(0.0f, -3.0f, -10.0f));
	camera->AddComponent<Camera>();
	camera->AddComponent<TestComponent>();
}

void Engine::EngineLoop()
{
	while (!glfwWindowShouldClose(window))
	{
		Time::FrameStart();

		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		scene->Process();
		glfwSwapBuffers(window);
	}
}