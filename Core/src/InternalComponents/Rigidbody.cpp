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
	if (isDynamic)
	{
		//transform->rotation = Quaternion(0.0f, 0.0f, 0.0f);
		//btQuaternion myQuat = transform->rotation;
		//std::cout << "BulletRotation = " << std::format("{}, {}, {}, {}", myQuat.getX(), myQuat.getY(), myQuat.getZ(), myQuat.getW()) << std::endl;

		////physicsTransform.setRotation(myQuat);
		//glm::quat glmquat = transform->rotation;
		//std::cout << "Transform->Rotation = " << std::format("{}, {}, {}, {}", transform->rotation.x, transform->rotation.y, transform->rotation.z, transform->rotation.w) << std::endl;
		//btQuaternion quat = transform->rotation;
		//std::cout << "BulletRotation = " << std::format("{}, {}, {}, {}", quat.getX(), quat.getY(), quat.getZ(), quat.getW()) << std::endl;
		//btQuaternion quat2 = btQuaternion(0.0f, 0.0f, 0.0f);
		//std::cout << "BulletRotation2 = " << std::format("{}, {}, {}, {}", quat2.getX(), quat2.getY(), quat2.getZ(), quat2.getW()) << std::endl;
		/*Quaternion castedQuat = quat;
		std::cout << "CastedQuaternion = " << castedQuat << std::endl;*/
		//std::cout << transform->rotation << std::endl;
		//physicsTransform.setRotation(transform->rotation);
	}
	//std::cout << transform->position << std::endl;
	//std::cout << transform->rotation << std::endl;
	
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
	//btVector3 gravity = physicsRigidbody->getGravity();
	//std::cout << std::format("Gravity = {}, {}, {}", gravity.x(), gravity.y(), gravity.z()) << std::endl;
	auto transform = GetTransform();
	btTransform& bulletTransform = physicsRigidbody->getWorldTransform();
	auto vec = bulletTransform.getOrigin();
	//std::cout << std::format("{}, {}, {}", vec.getX(), vec.getY(), vec.getZ()) << std::endl;
	//std::cout << transform->position << std::endl;
	transform->position = bulletTransform.getOrigin();
	transform->rotation = bulletTransform.getRotation();
	//std::cout << transform->position << std::endl;
	return;

	/*auto transform2 = GetTransform();
	float ptr[16];
	physicsRigidbody->getWorldTransform().getOpenGLMatrix(ptr);
	transform2->transformMatrix = glm::mat4(ptr[0], ptr[1], ptr[2], ptr[3], ptr[4], ptr[5], ptr[6], ptr[7], ptr[8], ptr[9], ptr[10], ptr[11], ptr[12], ptr[13], ptr[14], ptr[15]);
	return;*/

}

void Rigidbody::OnGUI()
{
	ImGui::Text(std::format("IsDynamic = {}", isDynamic).c_str());
	ImGui::Text(std::format("Mass = {}", mass).c_str());
}