#include "GameObject.h"
#include "Component.h"
#include <iostream>

GameObject::GameObject(std::string name)
{
	this->name = name;
}

void GameObject::InvokeAwake()
{
	for (auto& component : m_componentList)
	{
		if (component->enabled)
			component->Awake();
	}
}

void GameObject::InvokeBeforeRender()
{
	for (auto& component : m_componentList)
	{
		if (component->enabled)
			component->BeforeRender();
	}
}

void GameObject::InvokeRender(float deltaTime)
{
	transform->ResetCalculated();
	for (auto& component : m_componentList)
	{
		if (component->enabled)
			component->Render();
	}
}

void GameObject::InvokeEarlyUpdate(float deltaTime)
{
	for (auto& component : m_componentList)
	{
		if (component->enabled)
			component->EarlyUpdate(deltaTime);
	}
}

void GameObject::InvokeUpdate(float deltaTime)
{
	for (auto& component : m_componentList)
	{
		if(component->enabled)
			component->Update(deltaTime);
	}
}

void GameObject::InvokeLateUpdate(float deltaTime)
{
	for (auto& component : m_componentList)
	{
		if (component->enabled)
			component->LateUpdate(deltaTime);
	}
}

void GameObject::InvokeBeforeFixedUpdate()
{
	for (auto& component : m_componentList)
	{
		if (component->enabled)
			component->BeforeFixedUpdate();
	}
}

void GameObject::InvokeFixedUpdate(float fixedDeltaTime)
{
	for (auto& component : m_componentList)
	{
		if (component->enabled)
			component->FixedUpdate(fixedDeltaTime);
	}
}