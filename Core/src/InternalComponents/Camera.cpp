#include "Camera.h"
#include "GLM/glm/mat4x4.hpp"
#include "GLM/glm/gtc/matrix_transform.hpp"
#include "Globals.h"
#include "Transform.h"

Camera::Camera() noexcept
{
	Shader::SetPointers(&viewMatrix, &projectionMatrix, &position);
}

void Camera::BeforeRender()
{
	auto transform = GetTransform();
	position = transform->position;
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1), position);
	
	glm::mat4 rotationMatrix = glm::toMat4(transform->rotation);

	transformMatrix = translationMatrix * rotationMatrix;
	viewMatrix = glm::inverse(rotationMatrix) * translationMatrix;
	projectionMatrix = glm::perspective(glm::radians(verticalFOV), ((float)WINDOW_WIDTH / WINDOW_HEIGHT), nearClip, farClip);
}