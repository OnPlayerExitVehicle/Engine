#pragma once
#include "GameObject.h"
#include "bullet3-3.24/src/btBulletDynamicsCommon.h"
#include "BoxCollider.h"

class Rigidbody : public Component
{
public:
	Rigidbody();
	Rigidbody(float mass);

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

public:
	void OnGUI() override;

	std::string GetName() override { return typeid(*this).name(); }
};