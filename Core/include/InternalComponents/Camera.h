#pragma once
#include "Component.h"
#include "Shader.h"
#include "MeshRenderer.h"

class Camera : public Component
{
private:
	glm::mat4 transformMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	glm::vec3 position;

	const float farClip		= 100.0f;
	const float nearClip	= 1.0f;
	const float verticalFOV = 90.0f;

protected:
	void BeforeRender() override;

public:
	Camera() noexcept;
	std::string GetName() override { return typeid(*this).name(); }
};