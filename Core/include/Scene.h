#pragma once
#include "GameObject.h"
#include <GLM/glm/vec3.hpp>
#include "Singleton.h"
#include "bullet3-3.24/src/btBulletDynamicsCommon.h"
#include "GUI.h"

class Rigidbody;

class Scene
{
public:
	static Scene* Instance;

	Scene(GLFWwindow* window);
	void Process();
	void ProcessFixedUpdate();

	std::shared_ptr<GameObject> CreateObject(const std::string& name, const Vector3& position = Vector3(), const Quaternion& rotation = Quaternion(), const Vector3& scale = Vector3(1.0f), std::shared_ptr<Transform> parent = nullptr);
private:
	friend class GUI;
	friend class Rigidbody;

	void RegisterPhysicsObject(btRigidBody* rigidBody);

	std::vector<std::shared_ptr<GameObject>> objectList;
	std::vector<btRigidBody*> physicsObjectList;

	btDynamicsWorld* physicsWorld;
	btDispatcher* physicsDispatcher;
	btBroadphaseInterface* physicsBroadPhase;
	btConstraintSolver* physicsSolver;
	btCollisionConfiguration* physicsCollisionConfig;
	GUI gui;
};