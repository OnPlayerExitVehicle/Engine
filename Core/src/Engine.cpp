#include "Engine.h"
#include "PlaneCollider.h"
#include "Input.h"
#include "Camera.h"
#include "TestComponent.h"
#include "HTime.h"
#include "Rigidbody.h"
#include "TextureLoader.h"
#include "ObjectLoader.h"
#include "Vehicle.h"

Engine::Engine(int windowWidth, int windowHeight)
{
	srand(time(NULL));
	InitWindow(windowWidth, windowHeight);
	InitGraphics();

	scene = new Scene(window);
	Input::Initialize(window);
	glfwSetKeyCallback(window, Input::OnKeyPressedCallback);

	InitDefaultBehaviour();

	ObjectLoader loader;
	auto vehicle = loader.LoadGameObject(scene, OBJECTS_DIRECTORY"audi_a7_55_tfsi.fbx");
	vehicle->AddComponent<BoxCollider>()->SetLocalScaling({3.0f, 2.0f, 5.0f});
	vehicle->AddComponent<Rigidbody>(10.0f);
	vehicle->AddComponent<Vehicle>();
	/*auto character = scene->CreateObject("Character", Vector3(), Quaternion(), Vector3(0.01f, 0.01f, 0.01f));
	character->AddComponent<MeshRenderer>(std::move(mesh));
	character->GetComponent<MeshRenderer>()->GetMaterial().color = {0.0f, 1.0f, 1.0f};
	character->transform->scale = {0.01f, 0.01f, 0.01f};*/
}

void Engine::InitWindow(int windowWidth, int windowHeight)
{
    int ret = glfwInit();
    if(!ret)
    {
        std::cerr << ret << std::endl;
        return;
    }
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    int monitorCount = 0;
    GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);
    assert(monitorCount);
    int xPos, yPos, width, height;
    glfwGetMonitorWorkarea(monitors[0], &xPos, &yPos, &width, &height);
    window = glfwCreateWindow(width, height, std::format("Engine ({} bit)", sizeof(void*) * 8).c_str(), nullptr, nullptr);
	assert(window);
}

void APIENTRY debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    if(id != 131185)
        std::cout << std::format("Debug callback = [source={}][type={}][id={}][message={}]", source, type, id, message) << std::endl;
}

void Engine::InitGraphics()
{
	glfwMakeContextCurrent(window);
	(void)gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
    //glEnable(GL_DEBUG_OUTPUT);
    //glDebugMessageCallback(debug_callback, nullptr);
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
    while (!glfwWindowShouldClose(window)) {
        Time::FrameStart();
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        scene->Process();
        glfwSwapBuffers(window);
    }
}
