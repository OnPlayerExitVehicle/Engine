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

	const float farClip		= 100.0f;
	const float nearClip	= 1.0f;
	const float verticalFOV = 90.0f;

	std::shared_ptr<Shader> defaultShader;

protected:
	void BeforeRender() override;

public:
	std::string GetName() override { return typeid(*this).name(); }
};