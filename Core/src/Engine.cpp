#include "Engine.h"
#include "PlaneCollider.h"
#include "Input.h"
#include "Camera.h"
#include "TestComponent.h"
#include "HTime.h"
#include "Rigidbody.h"
#include "TextureLoader.h"
#include "ObjectLoader.h"

Engine::Engine(int windowWidth, int windowHeight)
{
	srand(time(NULL));
	InitWindow(windowWidth, windowHeight);
	InitGraphics();

	scene = new Scene(window);
	Input::Initialize(window);
	glfwSetKeyCallback(window, Input::OnKeyPressedCallback);

	InitDefaultBehaviour();

	/*ObjectLoader loader;
	auto mesh = loader.LoadObject(OBJECTS_DIRECTORY"teapot2.obj");
	auto teapot = scene->CreateObject("Teapot");
	teapot->AddComponent<MeshRenderer>(std::move(mesh));*/
}

void Engine::InitWindow(int windowWidth, int windowHeight)
{
	assert(glfwInit());
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window = glfwCreateWindow(windowWidth, windowHeight, std::format("Engine ({} bit)", sizeof(void*) * 8).c_str(), nullptr, nullptr);
	assert(window);
}

void Engine::InitGraphics()
{
	glfwMakeContextCurrent(window);
	(void)gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
}

void Engine::InitDefaultBehaviour()
{
	auto plane = scene->CreateObject("Plane", Vector3(0.0f, -0.5f, 0.0f), Quaternion(), Vector3(20.0f, 0.0f, 20.0f));
	plane->AddComponent<PlaneCollider>();
	plane->AddComponent<Rigidbody>();
	plane->AddComponent<MeshRenderer>(TextureLoader::LoadTexture(TEXTURES_DIRECTORY"brick.jpg"));

	auto camera = scene->CreateObject("Camera", Vector3(0.0f, -3.0f, -10.0f));
	camera->AddComponent<Camera>();
	camera->AddComponent<TestComponent>();

	auto light = scene->CreateObject("Light", Vector3(0.0f, 2.5f, 0.0f));
	light->AddComponent<MeshRenderer>(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), true);
	light->AddComponent<LightSource>();

	auto go = scene->CreateObject("Cube", Vector3(3.0f, 0.0f, 0.0f));
	go->AddComponent<MeshRenderer>(TextureLoader::LoadTexture(TEXTURES_DIRECTORY"container2.png"));
	go->AddComponent<BoxCollider>();

	/*auto go2 = scene->CreateObject("Cube 2", Vector3(-3.0f, 0.0f, 0.0f));
	go2->AddComponent<MeshRenderer>(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	go2->AddComponent<BoxCollider>();
	go2->AddComponent<Rigidbody>(10.0f);

	auto go3 = scene->CreateObject("Cube 3", Vector3(-3.0f, 0.0f, -3.0f));
	go3->AddComponent<MeshRenderer>(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	go3->AddComponent<BoxCollider>();
	go3->AddComponent<Rigidbody>(10.0f);

	auto go4 = scene->CreateObject("Cube 4", Vector3(3.0f, 0.0f, -3.0f));
	go4->AddComponent<MeshRenderer>(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
	go4->AddComponent<BoxCollider>();
	go4->AddComponent<Rigidbody>(10.0f);*/
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
