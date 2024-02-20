#pragma once
#include <type_traits>
#include <vector>
#include <memory>
#include "Component.h"

class Component;
class Transform;

class GameObject : public std::enable_shared_from_this<GameObject>
{
private:
	friend class GUI;

	std::vector<std::shared_ptr<Component>> m_componentList;
	
	void InvokeAwake();
	void InvokeBeforeRender();
	void InvokeRender(float deltaTime);
	void InvokeEarlyUpdate(float deltaTime);
	void InvokeUpdate(float deltaTime);
	void InvokeLateUpdate(float deltaTime);
	void InvokeBeforeFixedUpdate();
	void InvokeFixedUpdate(float fixedDeltaTime);

	friend class Scene;

public:
	GameObject(std::string name);

	std::shared_ptr<Transform> transform = nullptr;
	std::string name;
	bool lastlySelected = false;
	
	Event<void(const GameObject&)> onCollision;

	template <typename T, typename... Types>
	std::shared_ptr<T> AddComponent(Types... args)
	{
		static_assert(std::is_base_of<Component, T>(), "Type parameter of the function must derive from Component class!");

		std::shared_ptr<T> component_not_casted = std::make_shared<T>(args...);
		std::shared_ptr<Component> component = component_not_casted;
		m_componentList.push_back(component);

		component->m_transform = transform;
		component->m_object = shared_from_this();
		component->Awake();

		return component_not_casted;
	}

	template <typename T>
	std::shared_ptr<T> GetComponent()
	{
		static_assert(std::is_base_of<Component, T>(), "Type parameter of the function must derive from Component class!");

		for (std::shared_ptr<Component> component : m_componentList)
		{
			std::shared_ptr<T> sPtr = std::dynamic_pointer_cast<T>(component);
			if (sPtr != nullptr)
				return sPtr;
		}

		return std::shared_ptr<T>(nullptr);
	}

	template <typename T>
	bool TryGetComponent(_Out_ std::shared_ptr<T>& ptr)
	{
		static_assert(std::is_base_of<Component, T>(), "Type parameter of the function must derive from Component class!");

		for (std::shared_ptr<Component> component : m_componentList)
		{
			std::shared_ptr<T> sPtr = std::dynamic_pointer_cast<T>(component);
			if (sPtr != nullptr)
			{
				ptr = sPtr;
				return true;
			}
		}
		return false;
	}

	template <typename T>
	bool HasComponent() const
	{
		static_assert(std::is_base_of<Component, T>(), "Type parameter of the function must derive from Component class!");

		for (std::shared_ptr<Component> component : m_componentList)
		{
			std::shared_ptr<T> sPtr = std::dynamic_pointer_cast<T>(component);
			if (sPtr != nullptr)
				return true;
		}

		return false;
	}
};