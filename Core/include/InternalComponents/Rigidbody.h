#pragma once
#include "GameObject.h"
#include "Bullet/src/btBulletDynamicsCommon.h"
#include "BoxCollider.h"

class Rigidbody : public Component
{
public:
	Rigidbody();
	Rigidbody(float mass);

	void ActivatePhysics();
	void SetVelocity(const Vector3& velocity);
	void AddForce(const Vector3& force);
	void AddForce(const Vector3& force, const Vector3& relativePosition);
	void ApplyTorque(const Vector3& torque);
	void ApplyImpulse(const Vector3& impulse, const Vector3& relativePosition);
	void ApplyPushImpulse(const Vector3& impulse, const Vector3& relativePosition);
	

private:

	btTransform physicsTransform;
	btMotionState* physicsMotion;
	btRigidBody* physicsRigidbody;

	bool isDynamic;
	float mass;

protected:
	void Awake() override;
	void BeforeFixedUpdate() override;
	void FixedUpdate(float fixedDeltaTime) override;
	void OnCollision(const GameObject& other);

public:
	void OnGUI() override;

	std::string GetName() override { return typeid(*this).name(); }
};