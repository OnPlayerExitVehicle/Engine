#include "TestComponent.h"
#include "Input.h"
#include <iostream>
#include "GameObject.h"
#include "Camera.h"

void TestComponent::Awake()
{
	isCamera = GetObject()->HasComponent<Camera>();
}

void TestComponent::Update(float deltaTime)
{
	auto transform = GetTransform();

	if (isCamera || true)
	{
		Vector3 movePosition(0.0f, 0.0f, 0.0f);
		Vector3 rotation(0);
		/*std::cout <<
			movePosition.x << ", " <<
			movePosition.y << ", " <<
			movePosition.z << std::endl;*/

		if (Input::GetKey(KeyCode::A))
			movePosition += Vector3::Right;
		else if (Input::GetKey(KeyCode::D))
			movePosition -= Vector3::Right;

		if (Input::GetKey(KeyCode::W))
			movePosition += Vector3::Forward;
		else if (Input::GetKey(KeyCode::S))
			movePosition -= Vector3::Forward;

		if (Input::GetKey(KeyCode::LEFT_SHIFT))
			movePosition += Vector3::Up;
		else if (Input::GetKey(KeyCode::SPACE))
			movePosition -= Vector3::Up;

		if (Input::GetKey(KeyCode::Q))
			rotation += Vector3::Up;
		else if (Input::GetKey(KeyCode::E))
			rotation -= Vector3::Up;

		transform->position += (movePosition * (deltaTime * 10.0f));
		//transform->rotation += (rotation * (deltaTime * 30.0f));
	}
	else
	{
		Vector3 movePosition(0);

		if (Input::GetKey(KeyCode::Z))
			movePosition -= Vector3::Forward;

		transform->position += (movePosition * (deltaTime * 10.0f));

	}
}