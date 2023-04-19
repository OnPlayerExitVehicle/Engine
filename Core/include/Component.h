#pragma once
#include <functional>
#include <memory>
#include "Transform.h"

class GameObject;
class GUI;

class Component
{
private:
	std::weak_ptr<GameObject>   m_object;
	std::weak_ptr<Transform> m_transform;
	friend class GameObject;
	friend class GUI;

protected:
	virtual void Awake();
	virtual void BeforeRender();
	virtual void Render();
	virtual void EarlyUpdate(float deltaTime);
	virtual void Update(float deltaTime);
	virtual void LateUpdate(float deltaTime);
	virtual void BeforeFixedUpdate();
	virtual void FixedUpdate(float fixedDeltaTime);
	virtual void OnDestroy();
	
public:
	virtual void OnGUI();

	bool enabled = true;

	virtual ~Component();

	virtual std::string GetName() = 0;

	std::shared_ptr<GameObject> GetGameObject() const;

	std::shared_ptr<Transform> GetTransform() const;
};
