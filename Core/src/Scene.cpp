#include "Scene.h"
#include "Transform.h"
#include "HTime.h"
#include <exception>
#include <iostream>
#include "MeshRenderer.h"
#include <functional>
#include "Vehicle.h"

Scene* Scene::Instance;

Scene::Scene(GLFWwindow* window) : networkClient(this)
{
	gui.Init(window, &physicsDrawer);
	assert(Instance == nullptr);
	Instance = this;

	physicsCollisionConfig = new btDefaultCollisionConfiguration();
	physicsDispatcher	   = new btCollisionDispatcher(physicsCollisionConfig);
	physicsBroadPhase	   = new btDbvtBroadphase();
	physicsSolver		   = new btSequentialImpulseConstraintSolver();
	physicsWorld		   = new btDiscreteDynamicsWorld(physicsDispatcher, physicsBroadPhase, physicsSolver, physicsCollisionConfig);

	physicsWorld->setGravity(btVector3(.0f, -9.81f, .0f));
	physicsWorld->setDebugDrawer(&physicsDrawer);
	physicsDrawer.setDebugMode(btIDebugDraw::DBG_DrawWireframe);

	gContactAddedCallback = &Scene::ContactAddedCallback;
	auto& solverInfo = physicsWorld->getSolverInfo();
	solverInfo.m_erp = 0.5;
	solverInfo.m_erp2 = 0.5;
}

void Scene::Process()
{
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

	gui.Draw();

	for(auto& go : objectList)
	{
		std::shared_ptr<Vehicle> vehicle;
		if(go->TryGetComponent(vehicle))
		{
			const btRaycastVehicle* nativeVehicle = vehicle->GetNativeVehiclePtr();
			for(unsigned int i = 0U; i < nativeVehicle->getNumWheels(); i++)
			{
				//const btTransform tr = nativeVehicle->getWheelInfo(i).m_worldTransform;
				physicsDrawer.drawCylinder(nativeVehicle->getWheelInfo(i).m_wheelsRadius, nativeVehicle->getWheelInfo(i).m_wheelsRadius * 0.5f, 1, nativeVehicle->getWheelInfo(i).m_worldTransform, btVector3(0.0f, 1.0f, 0.0f));
				//physicsDrawer.drawLine(nativeVehicle->getChassisWorldTransform().getOrigin(), nativeVehicle->getWheelInfo(i).m_worldTransform.getOrigin(), btVector3(1, 1, 1));
			}
		}
	}
	physicsDrawer.Render();
}

void Scene::ProcessFixedUpdate()
{
	for (auto& go : objectList)
		go->InvokeBeforeFixedUpdate();
		
	float fixedDeltaTime = Time::FixedDt;
	physicsWorld->stepSimulation(fixedDeltaTime);
	physicsWorld->debugDrawWorld();

	for (auto& go : objectList)
		go->InvokeFixedUpdate(fixedDeltaTime);	
}

void Scene::ProcessNetworkUpdate()
{
	networkClient.ProcessNetworkUpdate(Time::NetworkDt);
}

bool Scene::IsConnected() const
{
	return networkClient.IsConnected();
}

void Scene::ConnectToServer(const std::string& address, uint16_t port)
{
	std::cout << "Address = [" << address << "], Port = " << port << std::endl;
	(void)networkClient.Connect(address, port);
}


void Scene::RegisterPhysicsObject(btRigidBody* rigidBody)
{
	physicsObjectList.push_back(rigidBody);
	physicsWorld->addRigidBody(rigidBody);
}

btDynamicsWorld* Scene::GetDynamicsWorld() const noexcept
{
	return physicsWorld;
}

bool Scene::ContactAddedCallback(btManifoldPoint& contactPoint, const btCollisionObjectWrapper* object1, int id0, int index0, const btCollisionObjectWrapper* object2, int id1, int index1)
{
	GameObject* go1 = static_cast<GameObject*>(object1->getCollisionObject()->getUserPointer());
	GameObject* go2 = static_cast<GameObject*>(object2->getCollisionObject()->getUserPointer());

	go1->onCollision.Invoke(*go2);
	go2->onCollision.Invoke(*go1);
	
	return false;
}

std::shared_ptr<GameObject> Scene::CreateObject(const std::string& name, const Vector3& position, const Quaternion& rotation, const Vector3& scale, std::shared_ptr<Transform> parent)
{
	std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>(name);
	gameObject->transform = std::make_shared<Transform>(gameObject);
	objectList.push_back(gameObject);
	gameObject->transform->position = position;
	gameObject->transform->rotation = rotation;
	gameObject->transform->scale	= scale;
	if(parent)
	{
		gameObject->transform->SetParent(parent);
	}
	

	gameObject->InvokeAwake();

	return gameObject;
}