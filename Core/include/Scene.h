#pragma once
#include <map>

#include "GameObject.h"
#include "Singleton.h"
#include "Bullet/src/btBulletDynamicsCommon.h"
#include "GUI.h"
#include "NetworkClient.h"
#include "Window.h"

class Rigidbody;

class Scene
{
public:
	static Scene* Instance;

	Scene(Window* window);
	void Process();
	void ProcessFixedUpdate();

	std::shared_ptr<GameObject> CreateObject(const std::string& name, const Vector3& position = Vector3(), const Quaternion& rotation = Quaternion(), const Vector3& scale = Vector3(1.0f), std::shared_ptr<Transform> parent = nullptr);
private:
	friend class GUI;
	friend class Rigidbody;

	bool IsConnected() const;
	void ConnectToServer(const std::string& address, uint16_t port);
	void RegisterPhysicsObject(btRigidBody* rigidBody);
	static bool ContactAddedCallback(btManifoldPoint&, const btCollisionObjectWrapper*, int, int, const btCollisionObjectWrapper*, int, int);

	std::vector<std::shared_ptr<GameObject>> objectList;
	std::vector<btRigidBody*> physicsObjectList;

	btDynamicsWorld* physicsWorld;
	btDispatcher* physicsDispatcher;
	btBroadphaseInterface* physicsBroadPhase;
	btConstraintSolver* physicsSolver;
	btCollisionConfiguration* physicsCollisionConfig;
	GUI gui;

	
	/*std::map<uint32_t, std::shared_ptr<Transform>> networkTransformMap;
	std::vector<std::shared_ptr<Transform>> localNetworkObjects;*/

public:
	void ProcessNetworkUpdate();
	NetworkClient networkClient;
};