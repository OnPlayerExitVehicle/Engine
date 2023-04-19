#include "Component.h"

void Component::Awake() { }
void Component::BeforeRender() { }
void Component::Render() { }
void Component::EarlyUpdate(float deltaTime) { }
void Component::Update(float deltaTime) { }
void Component::LateUpdate(float deltaTime) { }
void Component::BeforeFixedUpdate() { }
void Component::FixedUpdate(float fixedDeltaTime) { }
void Component::OnDestroy() { }
void Component::OnGUI() { } // public

std::shared_ptr<GameObject> Component::GetGameObject() const
{
	if (!m_object.expired())
	{
		return m_object.lock();
	}
	return nullptr;
}

std::shared_ptr<Transform> Component::GetTransform() const
{
	if (!m_transform.expired())
	{
		return m_transform.lock();
	}
	return nullptr;
}

Component::~Component() { }