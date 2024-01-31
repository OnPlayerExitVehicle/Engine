#include "Scene.h"
#include "Transform.h"
#include "HTime.h"
#include <exception>
#include <iostream>
#include "MeshRenderer.h"

Scene* Scene::Instance;

Scene::Scene(GLFWwindow* window) : networkClient(this)
{
	gui.Init(window);
	assert(Instance == nullptr);
	Instance = this;

	physicsCollisionConfig = new btDefaultCollisionConfiguration();
	physicsDispatcher	   = new btCollisionDispatcher(physicsCollisionConfig);
	physicsBroadPhase	   = new btDbvtBroadphase();
	physicsSolver		   = new btSequentialImpulseConstraintSolver();
	physicsWorld		   = new btDiscreteDynamicsWorld(physicsDispatcher, physicsBroadPhase, physicsSolver, physicsCollisionConfig);

	physicsWorld->setGravity(btVector3(.0f, -9.81f, .0f));

	//networkClient.Connect("127.0.0.1", 60000);
}

void Scene::Process()
{
	gui.Draw();
	float dt = Time::Dt;

	for (auto& go : objectList)
		go->InvokeEarlyUpdate(dt);

	for (auto& go : objectList)
		go->InvokeUpdate(dt);

	for (auto& go : objectList)
		go->InvokeLateUpdate(dt);

	for (auto& go : objectList)
		go->InvokeBeforeRender();

	for (auto& go : objectList)
		go->InvokeRender(dt);
}

void Scene::ProcessFixedUpdate()
{
	for (auto& go : objectList)
		go->InvokeBeforeFixedUpdate();
		
	float fixedDeltaTime = Time::FixedDt;
	physicsWorld->stepSimulation(fixedDeltaTime);

	for (auto& go : objectList)
		go->InvokeFixedUpdate(fixedDeltaTime);
}

void Scene::ProcessNetworkUpdate()
{
	networkClient.ProcessNetworkUpdate(Time::NetworkDt);
}


void Scene::RegisterPhysicsObject(btRigidBody* rigidBody)
{
	physicsObjectList.push_back(rigidBody);
	physicsWorld->addRigidBody(rigidBody);
}

std::shared_ptr<GameObject> Scene::CreateObject(const std::string& name, const Vector3& position, const Quaternion& rotation, const Vector3& scale, std::shared_ptr<Transform> parent)
{
	std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>(name);
	gameObject->transform = std::make_shared<Transform>(gameObject);
	objectList.push_back(gameObject);
	gameObject->transform->position = position;
	gameObject->transform->rotation = rotation;
	gameObject->transform->scale	= scale;
	gameObject->transform->parent	= parent;

	gameObject->InvokeAwake();

	return gameObject;
}