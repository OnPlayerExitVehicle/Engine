#include "Rigidbody.h"
#include "Exceptions.h"
#include "Scene.h"
#include "Globals.h"
#include <iostream>
#include "GUI.h"

Rigidbody::Rigidbody()			 : isDynamic(false), mass(.0f) { }

Rigidbody::Rigidbody(float mass) : isDynamic(true), mass(mass) { }

void Rigidbody::Awake()
{
	std::cout << "Awake" << std::endl;
	auto gameObject = this->GetGameObject();
	
	std::shared_ptr<Collider> collider;
	if (!gameObject->TryGetComponent<Collider>(collider))
		throw new ColliderNotFoundException("Collider not found!");

	auto transform = GetTransform();

	physicsTransform.setIdentity();
	physicsTransform.setOrigin(transform->position);
	physicsTransform.setRotation(transform->rotation);
	
	physicsMotion = new btDefaultMotionState(physicsTransform);
	if (!isDynamic)
	{
		physicsRigidbody = new btRigidBody(mass, physicsMotion, collider->GetBulletCollider());
	}
	else
	{
		btVector3 inertia;

		btBoxShape* collisionShape = (btBoxShape*)collider->GetBulletCollider();

		collisionShape->calculateLocalInertia(mass, inertia);

		physicsRigidbody = new btRigidBody(mass, physicsMotion, collisionShape, inertia);
	}
	Scene::Instance->RegisterPhysicsObject(physicsRigidbody);
}

void Rigidbody::BeforeFixedUpdate()
{
	auto transform = GetTransform();

	physicsTransform.setOrigin(transform->position);
	physicsTransform.setRotation(transform->rotation);
	Collider collider;
	GetGameObject()->GetComponent<Collider>()->GetBulletCollider()->setLocalScaling(transform->scale);
	//physicsMotion->setWorldTransform(physicsTransform);
	physicsRigidbody->setWorldTransform(physicsTransform);

}

void Rigidbody::FixedUpdate(float fixedDeltaTime)
{
	auto transform = GetTransform();
	btTransform& bulletTransform = physicsRigidbody->getWorldTransform();
	auto vec = bulletTransform.getOrigin();
	transform->position = bulletTransform.getOrigin();
	transform->rotation = bulletTransform.getRotation();
}

void Rigidbody::OnGUI()
{
	ImGui::Text(std::format("IsDynamic = {}", isDynamic).c_str());
	ImGui::Text(std::format("Mass = {}", mass).c_str());
}