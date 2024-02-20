#include "Rigidbody.h"
#include "Exceptions.h"
#include "Scene.h"
#include "Globals.h"
#include <iostream>
#include "GUI.h"
#include "MeshRenderer.h"

Rigidbody::Rigidbody() : isDynamic(false), mass(.0f) { }

Rigidbody::Rigidbody(float mass) : isDynamic(true), mass(mass)
{
	
}

void Rigidbody::Awake()
{
	auto gameObject = this->GetGameObject();

	/*if (isDynamic)
		gameObject->onCollision.AddListener(std::bind(&Rigidbody::OnCollision, this, std::placeholders::_1));*/

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

	physicsRigidbody->setCollisionFlags(physicsRigidbody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
	physicsRigidbody->setUserPointer(GetGameObject().get());

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

void Rigidbody::OnCollision(const GameObject& other)
{
	std::shared_ptr<MeshRenderer> renderer;
	if (GetGameObject()->TryGetComponent<MeshRenderer>(renderer) && other.HasComponent<BoxCollider>())
	{
		renderer->SetColor(Vector3(1.0f, 0.0f, 0.0f));
	}
	std::cout << "OnCollision with " << other.name << std::endl;
}

void Rigidbody::OnGUI()
{
	if (ImGui::Button("Test"))
	{
		SetVelocity(Vector3(.0f, 10.0f, .0f));
	}

	ImGui::Text(std::format("IsDynamic = {}", isDynamic).c_str());
	ImGui::Text(std::format("Mass = {}", mass).c_str());
}

void Rigidbody::ActivatePhysics()
{
	physicsRigidbody->setActivationState(ACTIVE_TAG);
}

void Rigidbody::SetVelocity(const Vector3& velocity)
{
	ActivatePhysics();
	physicsRigidbody->setLinearVelocity(velocity);
}

void Rigidbody::AddForce(const Vector3& force)
{
	ActivatePhysics();
	physicsRigidbody->applyCentralForce(force);
}

void Rigidbody::AddForce(const Vector3& force, const Vector3& relativePosition)
{
	ActivatePhysics();
	physicsRigidbody->applyForce(force, relativePosition);
}

void Rigidbody::ApplyTorque(const Vector3& torque)
{
	ActivatePhysics();
	physicsRigidbody->applyTorque(torque);
}

void Rigidbody::ApplyImpulse(const Vector3& impulse, const Vector3& relativePosition)
{
	ActivatePhysics();
	physicsRigidbody->applyImpulse(impulse, relativePosition);
}

void Rigidbody::ApplyPushImpulse(const Vector3& impulse, const Vector3& relativePosition)
{
	ActivatePhysics();
	physicsRigidbody->applyPushImpulse(impulse, relativePosition);
}