#pragma once
#include <memory>
#include <vector>
#include "Vector3.h"
#include "Quaternion.h"
#include <GLM/glm/mat4x4.hpp>

class GameObject;
class Transform : public std::enable_shared_from_this<Transform>
{
public:
	Vector3									position;
	Quaternion								rotation;
	Vector3									scale;
	std::shared_ptr<Transform>				parent;
	std::vector<std::shared_ptr<Transform>>	childList;
	std::shared_ptr<GameObject> gameObject;

	/*glm::vec3 up;
	glm::vec3 right;
	glm::vec3 forward;*/

	Transform(std::shared_ptr<GameObject> object) : gameObject(object) { }
	const glm::mat4& GetTransformMatrix() const;
	void SetParent(std::shared_ptr<Transform> parent);

private:
	friend class MeshRenderer;
	friend class Camera;
	friend class Rigidbody;
	friend class GameObject;
	friend class GUI;

	glm::mat4 transformMatrix;
	bool calculatedThisFrame = false;
	bool drawByGuiThisFrame = false;

	void CalculateTransformMatrix();
	
	std::shared_ptr<Transform> GetParent() const;

	void ResetCalculated();
};
