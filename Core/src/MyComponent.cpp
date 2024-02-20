#include "MyComponent.h"
#include "Rigidbody.h"
#include "Input.h"

void MyComponent::Awake()
{
	std::shared_ptr<Rigidbody> rigidbody;
	if(GetGameObject()->TryGetComponent<Rigidbody>(rigidbody))
	{
		
	}
}

void MyComponent::Update(float deltaTime)
{
	if(Input::GetKey(KeyCode::E))
	{
		GetGameObject()->GetComponent<Rigidbody>()->AddForce(Vector3(0.0f, 50000.0f, 0.0f) * deltaTime);
	}
}

void MyComponent::OnGUI()
{

}
